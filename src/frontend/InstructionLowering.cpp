#include "minijavab/frontend/InstructionLowering.h"

#include "minijavab/frontend/PrimitiveTypes.h"
#include "minijavab/frontend/Converter.h"
#include "minijavab/frontend/ASTClassTable.h"
#include "minijavab/frontend/ImmediateFolder.h"

#include "minijavab/core/ir/Module.h"
#include "minijavab/core/ir/BasicBlock.h"
#include "minijavab/core/ir/IRBuilder.h"
#include "minijavab/core/ir/IntegerConstant.h"
#include "minijavab/core/ir/StringConstant.h"
#include "minijavab/core/ir/Instructions/Cmp.h"

using namespace MiniJavab::Core;

namespace MiniJavab {
namespace Frontend {

/// The maximum size of an array. We only support four dimensional arrays to simplify the 
/// intrinsic function invocation. Four was chosen somewhat randomly in that it ought to
/// be enough for most things
constexpr size_t MAX_ARRAY_DIMENSIONS = 4;

// TODO:
// - Make arrays stored as T* not T**

InstructionLowering::InstructionLowering(ASTConverter* converter)
                        : _converter(converter) {}

InstructionLowering::FunctionSymbolTable InstructionLowering::CreateLocalVariables(ASTMethod* methodDefinition) {
    FunctionSymbolTable functionSymbolTable;

    // Create local variables for each passed-in parameter
    for (auto [parameterName, parameter] : methodDefinition->Parameters) {
        IR::Parameter* functionParameter = _builder->Block->ParentFunction->GetParameterByName(parameterName);
        IR::Type* resolvedType = _converter->ResolveASTType(parameter->Type);

        // Create a new local variable as a copy of the passed-in parameter
        IR::Value* localVariable = _builder->CreateAlloc(resolvedType,
                                                            parameterName + ".local");
        
        // Store the passed-in parameter into the local variable
        _builder->CreateStore(functionParameter, localVariable);

        // Create two symbol table entries, one for the passed-in parameter and one for the copy
        FunctionSymbolEntry* localEntry = new FunctionSymbolEntry {
            /*Value*/ localVariable,
            /*isParameter*/ false,
            /*type*/ resolvedType->StripPointerCasts(),
            /*copiedSymbol*/ nullptr
        };

        FunctionSymbolEntry* parameterEntry = new FunctionSymbolEntry {
            /*Value*/ functionParameter,
            /*isParameter*/ true,
            /*type*/ resolvedType->StripPointerCasts(),
            /*copiedSymbol*/ localEntry
        };

        functionSymbolTable.insert({localVariable->Name, localEntry});
        functionSymbolTable.insert({parameterName, parameterEntry});
    }

    // Create local variables for each variable declaration in the method
    for (auto [variableName, variable] : methodDefinition->Variables) {
        IR::Type* resolvedType = _converter->ResolveASTType(variable->Type);
        IR::Value* localVariable = _builder->CreateAlloc(resolvedType,
                                                            variableName);

        functionSymbolTable.insert({variableName, new FunctionSymbolEntry {
            /*Value*/ localVariable,
            /*isParameter*/ false,
            /*type*/ resolvedType,
            /*copiedSymbol*/ nullptr
        }});
    }

    return functionSymbolTable;
}

IR::Value* InstructionLowering::GetVariablePointer(ASTVariable* variable) {
    if (variable == nullptr) {
        // Get `this` variable from function symbol table
        FunctionSymbolTable::iterator searchResult = _functionSymbolTable->find("this");
        assert(searchResult != _functionSymbolTable->end() && "Unable to find this symbol");
        return searchResult->second->copiedSymbol->Value;
    }
    else if (variable->ParentMethod == _methodDefinition) {
        // it's a local variable/parameter
        FunctionSymbolTable::iterator search = _functionSymbolTable->find(variable->Name);
        assert(search != _functionSymbolTable->end() && "unable to find local variable");

        return search->second->isParameter ? search->second->copiedSymbol->Value : search->second->Value;
    }
    else {
        // Get `this` variable from function symbol table
        FunctionSymbolTable::iterator searchResult = _functionSymbolTable->find("this");
        assert(searchResult != _functionSymbolTable->end() && "Unable to find this symbol");
        IR::Value* thisVariable = searchResult->second->copiedSymbol->Value;
        IR::Value* thisValue = _builder->CreateLoad(static_cast<IR::PointerType*>(thisVariable->ValueType)->ElementType, thisVariable);

        // Get offset into `this` where the local variable is stored
        IR::StructType* thisStruct = static_cast<IR::StructType*>(searchResult->second->Type);
        IR::Type* localVariableType = thisStruct->GetElementType(variable->Name);
        size_t variableOffset = thisStruct->GetElementOffset(variable->Name);

        // create a pointer to the local variable and then load it
        IR::Value* localVariablePointer = _builder->CreateGetPtr(thisValue, localVariableType, variableOffset);
        return localVariablePointer;
    }
}

IR::Value* InstructionLowering::GetArrayOffset(IR::Value* arrayPointer, AST::IndexNode* arrayIndices) {
    // TODO: cleanup comments
    IR::Value* currentPointer = _builder->CreateBitcast(arrayPointer, new IR::PointerType(PrimitiveTypes::Int()));

    for (size_t expressionIndex = 0; expressionIndex < arrayIndices->Expressions.size(); expressionIndex++) {
        AST::ExpNode* expression = arrayIndices->Expressions[expressionIndex];

        // Offset the array pointer to the location of the element we're assigning to
        IR::Value* loweredExpression = LowerExpression(expression);
        // Include the array header in the offset calculation
        _builder->CreateAdd(loweredExpression, new IR::Immediate(PrimitiveTypes::Int(), 1));
        currentPointer = _builder->CreateAdd(currentPointer, loweredExpression);

        // If this is the last index expression, assign the value to the current array pointer. Else
        // load the next array pointer from the current array pointer and run the loop again
        if (expressionIndex == arrayIndices->Expressions.size() - 1) {
            // Cast back to the correct pointer type before assignment
            return _builder->CreateBitcast(currentPointer, arrayPointer->ValueType);
        }
        else {
            IR::Value* castedPointer = _builder->CreateBitcast(currentPointer, new IR::PointerType(new IR::PointerType(PrimitiveTypes::Int())));
            currentPointer = _builder->CreateLoad(new IR::PointerType(PrimitiveTypes::Int()), castedPointer);
        }
    }
    assert(false); // unreachable
}

IR::Value* InstructionLowering::LowerObject(AST::ObjectNode* object) {
    if (object->IsNamedObject()) {
        AST::NamedObjectNode* namedObject = static_cast<AST::NamedObjectNode*>(object);
        if (namedObject->IsNewObject()) {
            IR::Module* mod = _function->GetContainingModule();

            // look up the class type of the symbol being created
            IR::StructType* classType = _converter->LookupClassType(namedObject->Name);
            assert(classType && "Failed to find class information");

            // call the intrinsic to create the new object
            IR::Function* newIntrinsic = mod->GetTypedIntrinsic(IR::MJ_NEW_INTRINSIC, classType);
            return _builder->CreateCall(newIntrinsic, {});
        }
        else {
            IR::Value* localVariable = GetVariablePointer(namedObject->Symbol);
            return _builder->CreateLoad(static_cast<IR::PointerType*>(localVariable->ValueType)->ElementType, localVariable);
        }
    }
    else if (object->IsThisObject()) {
        IR::Value* localVariable = GetVariablePointer(nullptr);
        return _builder->CreateLoad(static_cast<IR::PointerType*>(localVariable->ValueType)->ElementType, localVariable);
    }
    else if (object->IsNewArray()) {
        AST::NewArrayObjectNode* newArrayNode = static_cast<AST::NewArrayObjectNode*>(object);
        IR::Type* baseType = _converter->ResolveASTType(newArrayNode->Type->ResolveType());

        if (newArrayNode->Index->Expressions.size() > MAX_ARRAY_DIMENSIONS) {
            assert(false && "cannot construct multi-dimensional arrays greater than four dimensions"); 
        }

        // Lower the array construction expressions into individual call parameters
        std::vector<IR::Value*> arrayDimensions;
        arrayDimensions.reserve(MAX_ARRAY_DIMENSIONS);
        for (AST::ExpNode* expression : newArrayNode->Index->Expressions) {
            arrayDimensions.push_back(LowerExpression(expression));
        }

        // The call to mj.new_array expects four arguments, if we're allocating a smaller array just pad
        // the call with zeroes
        if (arrayDimensions.size() != MAX_ARRAY_DIMENSIONS) {
            for (size_t i = arrayDimensions.size(); i < MAX_ARRAY_DIMENSIONS; i++) {
                arrayDimensions.push_back(new IR::Immediate(PrimitiveTypes::Int(), 0));
            }
        }

        // Invoke mj.new_array to construct the array
        IR::Function* newArrayFunction = _function->GetContainingModule()->GetIntrinsic(IR::MJ_NEW_ARRAY_INTRINSIC);
        IR::Value* arrayPointer = _builder->CreateCall(newArrayFunction, arrayDimensions);

        return _builder->CreateBitcast(arrayPointer, new IR::PointerType(baseType));
    }

    assert(false && "unreachable");
}

IR::Value* InstructionLowering::LowerExpression(AST::LiteralExpNode* expression) {
    if (expression->IsIntegerLiteral()) {
        AST::IntegerLiteralExpNode* integerLiteralNode = static_cast<AST::IntegerLiteralExpNode*>(expression);
        return new IR::Immediate(PrimitiveTypes::Int(), integerLiteralNode->Value);
    }
    else if (expression->IsBooleanLiteral()) {
        AST::BooleanLiteralExpNode* booleanLiteralNode = static_cast<AST::BooleanLiteralExpNode*>(expression);
        return new IR::Immediate(PrimitiveTypes::Boolean(), booleanLiteralNode->Value);
    }
    else if (expression->IsStringLiteral()) {
        AST::StringLiteralExpNode* stringLiteralNode = static_cast<AST::StringLiteralExpNode*>(expression);
        assert(false && "string literals not supported yet");
    }
    assert(false && "unknown literal expression type");
}

IR::Value* InstructionLowering::LowerExpression(AST::BinaryExpNode* expression) {
    if (ImmediateFolder::CanFold(expression)) {
        return ImmediateFolder::Fold(expression);
    }

    IR::Value* leftHandSide = LowerExpression(expression->LeftSide);
    IR::Value* rightHandSide = LowerExpression(expression->RightSide);

    switch (expression->Operator) {
        case AST::OperatorType::Add: {
            return _builder->CreateAdd(leftHandSide, rightHandSide);
        }
        case AST::OperatorType::EqualTo: {
            return _builder->CreateCmp(IR::ComparisonOperation::Equal, leftHandSide, rightHandSide);
        }
        case AST::OperatorType::NotEqualTo: {
            return _builder->CreateCmp(IR::ComparisonOperation::NotEqual, leftHandSide, rightHandSide);
        }
        case AST::OperatorType::LessThan: {
            return _builder->CreateCmp(IR::ComparisonOperation::LessThan, leftHandSide, rightHandSide);
        }
        case AST::OperatorType::LessThanEqualTo: {
            return _builder->CreateCmp(IR::ComparisonOperation::LessThanEqualTo, leftHandSide, rightHandSide);
        }
        case AST::OperatorType::GreaterThan: {
            return _builder->CreateCmp(IR::ComparisonOperation::GreaterThan, leftHandSide, rightHandSide);
        }
        case AST::OperatorType::GreaterThanEqualTo: {
            return _builder->CreateCmp(IR::ComparisonOperation::GreaterThanEqualTo, leftHandSide, rightHandSide);
        }
        case AST::OperatorType::Subtract: {
            return _builder->CreateSub(leftHandSide, rightHandSide);
        }
        case AST::OperatorType::Multiply: {
            return _builder->CreateMul(leftHandSide, rightHandSide);
        }
        case AST::OperatorType::Divide: {
            return _builder->CreateDiv(leftHandSide, rightHandSide);
        }
        case AST::OperatorType::BooleanAnd: {
            return _builder->CreateAND(leftHandSide, rightHandSide);
        }
        case AST::OperatorType::BooleanOr: {
            return _builder->CreateOR(leftHandSide, rightHandSide);
        }
        default:
            _builder->Block->ParentFunction->Dump();
            assert(false ** "binary expression lowering not implemented yet");
    }
}

IR::Value* InstructionLowering::LowerExpression(AST::ObjectExpNode* expression) {
    return LowerObject(expression->Object);
}

IR::Value* InstructionLowering::LowerExpression(AST::UnaryExpNode* expression) {
    if (ImmediateFolder::CanFold(expression)) {
        return ImmediateFolder::Fold(expression);
    }

    IR::Value* loweredExpression = LowerExpression(expression->Expression);

    switch (expression->Operator) {
        case AST::OperatorType::Add:
            // +{int} is a nop operation
            return loweredExpression;
        case AST::OperatorType::Subtract: {
            // multiply the resultant expression by -1
            IR::IntegerType* valueType = static_cast<IR::IntegerType*>(loweredExpression->ValueType);
            IR::Immediate* negativeOne = new IR::Immediate(valueType, -1);
            
            return _builder->CreateMul(loweredExpression, negativeOne);
        }
        case AST::OperatorType::BooleanNot: {
            // We can perform the NOT operation by always XORing true
            // false XOR false = false 
            // false XOR true = true
            // true XOR false = true
            // true XOR true = false
            return _builder->CreateXOR(loweredExpression, new IR::Immediate(new IR::BooleanType(), true));
        }
        default:
            assert(false && "unrecognized unary operator");
    }
    return nullptr;
}

IR::Value* InstructionLowering::LowerExpression(AST::MethodCallExpNode* expression) {
    IR::Module* mod = _function->GetContainingModule();

    // Get the object we're calling
    IR::Value* loadedObject = LowerObject(expression->Object);

    // Set up the arguments for the call
    std::vector<IR::Value*> arguments(1 + expression->Expressions.size());
    // The first argument is always the object we're calling
    arguments[0] = loadedObject;

    for (size_t i = 0; i < expression->Expressions.size(); i++) {
        arguments[i + 1] = LowerExpression(expression->Expressions[i]);
    }

    // Lookup the method to call
    // todo: stow this away during AST parsing
    ASTMethod* methodSymbol = expression->CalledMethod; 
    IR::Function* calledFunction = mod->GetFunctionByName(methodSymbol->ParentClass->Name + "_" + methodSymbol->Name);

    // finally create the call with our arguments
    return _builder->CreateCall(calledFunction, arguments);
}

IR::Value* InstructionLowering::LowerExpression(AST::IndexExpNode* expression) {
    // Get the object we're loading from
    IR::Value* objectPointer = GetVariablePointer(expression->ObjectInfo);

    // Load the array from wherever it's stored
    // TODO: array is stored as pointer to array, dumb
    objectPointer = _builder->CreateLoad(objectPointer->ValueType->StripPointerCasts(), objectPointer);

    // Get the offset into the array where we should load from
    IR::Value* offsetPointer = GetArrayOffset(objectPointer, expression->Index);

    // Load it
    return _builder->CreateLoad(offsetPointer->ValueType->StripPointerCasts(), offsetPointer);
}

IR::Value* InstructionLowering::LowerExpression(AST::LengthExpNode* expression) {
    // Get the array we're examining
    IR::Value* objectPointer = GetVariablePointer(expression->ObjectInfo);

    // Load the array from wherever it's stored
    // TODO: array is stored as pointer to array, dumb
    objectPointer = _builder->CreateLoad(objectPointer->ValueType->StripPointerCasts(), objectPointer);

    if (expression->Index != nullptr) {
        // Update the pointer to the array within the multi-dimensional array
        objectPointer = GetArrayOffset(objectPointer, expression->Index);
    }

    // Call the length method on the array
    IR::Function* lengthFunction = _function->GetContainingModule()->GetIntrinsic(IR::MJ_ARRAY_LENGTH_INTRINSIC);
    objectPointer = _builder->CreateBitcast(objectPointer, new IR::PointerType(PrimitiveTypes::Int()));
    return _builder->CreateCall(lengthFunction, {objectPointer});
}

IR::Value* InstructionLowering::LowerExpression(AST::ExpNode* expression) {
    switch (expression->Kind) {
        case AST::ExpKind::Literal:
            return LowerExpression(static_cast<AST::LiteralExpNode*>(expression));
        case AST::ExpKind::Binary:
            return LowerExpression(static_cast<AST::BinaryExpNode*>(expression));
        case AST::ExpKind::Object:
            return LowerExpression(static_cast<AST::ObjectExpNode*>(expression));
        case AST::ExpKind::Unary:
            return LowerExpression(static_cast<AST::UnaryExpNode*>(expression));
        case AST::ExpKind::MethodCall:
            return LowerExpression(static_cast<AST::MethodCallExpNode*>(expression));
        case AST::ExpKind::Nested: {
            AST::NestedExpNode* nestedNode = static_cast<AST::NestedExpNode*>(expression);
            return LowerExpression(nestedNode->Expression);
        }
        case AST::ExpKind::Index: {
            return LowerExpression(static_cast<AST::IndexExpNode*>(expression));
        }
        case AST::ExpKind::LengthMethod: {
            return LowerExpression(static_cast<AST::LengthExpNode*>(expression));
        }
        default:
            _builder->Block->ParentFunction->Dump();
            assert(false && "expression lowering not implemented yet");
    }
}

IR::Value* InstructionLowering::LowerReturnExpression(AST::ExpNode* expression) {
    IR::Value* loweredExpression = expression != nullptr ? LowerExpression(expression) : nullptr;
    if (expression != nullptr) {
        return _builder->CreateRet(loweredExpression);
    }
    return _builder->CreateRet();
}

void InstructionLowering::LowerStatement(AST::AssignmentStatementNode* statement) {
    // Pointer to where we should assign the value to. Either the symbol pointer itself, or
    // an array pointer derived from the symbol pointer
    IR::Value* symbolPointer = GetVariablePointer(statement->AssignedVariable);
    IR::Value* originalPointer = symbolPointer;

    if (statement->IsIndexedAssignment()) { // assigning to an array
        // load the array from wherever it's stored
        // TODO: array is stored as pointer to array, dumb
        symbolPointer = _builder->CreateLoad(symbolPointer->ValueType->StripPointerCasts(), symbolPointer);
        AST::AssignmentIndexStatementNode* indexedAssignment = static_cast<AST::AssignmentIndexStatementNode*>(statement);

        // Get the offset into the array where we should store to
        IR::Value* offsetPointer = GetArrayOffset(symbolPointer, indexedAssignment->Index);

        // Store it
        IR::Value* toStore = LowerExpression(indexedAssignment->Expression);
        _builder->CreateStore(toStore, offsetPointer);
    }
    else { // assigning to a primitive
        IR::Value* assignmentValue = LowerExpression(statement->Expression);
        _builder->CreateStore(assignmentValue, symbolPointer);
    }
}

void InstructionLowering::LowerStatement(AST::MethodCallStatementNode* statement) {
    LowerExpression(statement->CallExpression);
}

void InstructionLowering::LowerStatement(AST::IfStatementNode* statement) {
    // 0: Create each control flow block to jump to
    IR::BasicBlock* ifBlock = _function->CreateBlock("if.then");
    IR::BasicBlock* elseBlock = _function->CreateBlock("if.else");
    IR::BasicBlock* ifExitBlock = _function->CreateBlock("if.exit");

    // 1: lower if conditional block and install jumps
    IR::Value* comparison = LowerExpression(statement->Expression);
    _builder->CreateBrIf(ifBlock, comparison);
    _builder->CreateBr(elseBlock);

    // 2: lower if block
    _builder->Block = ifBlock;
    LowerStatement(statement->IfStatement);
    _builder->CreateBr(ifExitBlock);

    // 3: lower else block
    _builder->Block = elseBlock;
    LowerStatement(statement->ElseStatement);
    _builder->CreateBr(ifExitBlock);

    // 4: Set next instructions to exit block
    _builder->Block = ifExitBlock;
}

void InstructionLowering::LowerStatement(AST::NestedStatementsNode* statement) {
    for (AST::StatementNode* nestedStatement : statement->Statements) {
        LowerStatement(nestedStatement);
    }
}

void InstructionLowering::LowerStatement(AST::PrintStatementNode* statement) {
    IR::Module* mod = _function->GetContainingModule();
    AST::LiteralExpNode* literalExpression = nullptr;
    if (statement->Expression->IsLiteralExpression()) {
        literalExpression = static_cast<AST::LiteralExpNode*>(statement->Expression);
    }

    if (statement->Expression->IsLiteralExpression() && literalExpression->IsStringLiteral()) {
        AST::StringLiteralExpNode* stringLiteral = static_cast<AST::StringLiteralExpNode*>(literalExpression);

        // Create a new global variable storing the string to print
        IR::GlobalVariable* constant = mod->AddStringConstant(stringLiteral->Value);

        // Call the print intrinsic with a pointer to the global string
        IR::Value* stringPointer = _builder->CreateGetPtr(constant, constant->ValueType);
        IR::Function* printFunction = mod->GetIntrinsic(IR::MJ_PRINTLN_STR_INTRINSIC);
        _builder->CreateCall(printFunction, {stringPointer});
    }
    else {
        // Lower the expression and call the print intrinsic
        IR::Value* immediate = LowerExpression(statement->Expression);
        IR::Function* printFunction = mod->GetIntrinsic(IR::MJ_PRINTLN_INT_INTRINSIC);
        _builder->CreateCall(printFunction, {immediate});
    }
}

void InstructionLowering::LowerStatement(AST::ReturnStatementNode* statement) {
    IR::Value* valueToReturn = LowerExpression(statement->Expression);
    _builder->CreateRet(valueToReturn);
}

void InstructionLowering::LowerStatement(AST::WhileStatementNode* statement) {
    // 0: Create each control flow block to jump to
    IR::BasicBlock* comparisonBlock = _function->CreateBlock("while.cmp");
    IR::BasicBlock* whileBody = _function->CreateBlock("while.body");
    IR::BasicBlock* whileExit = _function->CreateBlock("while.end");

    // 1: Swap to the comparison block and lower it
    _builder->Block = comparisonBlock;
    IR::Value* comparisonValue = LowerExpression(statement->Expression);

    // Jump to the body if the conditional was successful, else skip it
    _builder->CreateBrIf(whileBody, comparisonValue);
    _builder->CreateBr(whileExit);

    // 2: Swap to the body block and lower it
    _builder->Block = whileBody;
    LowerStatement(statement->Statement);
    _builder->CreateBr(comparisonBlock);

    // 3: Set next instructions to exit block
    _builder->Block = whileExit;
}

void InstructionLowering::LowerStatement(AST::StatementNode* statement) {
    statement->Dump();
    switch (statement->Kind) {
        case AST::StatementKind::Assignment:
            LowerStatement(static_cast<AST::AssignmentStatementNode*>(statement));
            break;
        case AST::StatementKind::If:
            LowerStatement(static_cast<AST::IfStatementNode*>(statement));
            break;
        case AST::StatementKind::Nested:
            LowerStatement(static_cast<AST::NestedStatementsNode*>(statement));
            break;
        case AST::StatementKind::Print:
            LowerStatement(static_cast<AST::PrintStatementNode*>(statement));
            break;
        case AST::StatementKind::Return:
            LowerStatement(static_cast<AST::ReturnStatementNode*>(statement));
            break;
        case AST::StatementKind::While:
            LowerStatement(static_cast<AST::WhileStatementNode*>(statement));
            break;
        case AST::StatementKind::MethodCall:
            LowerStatement(static_cast<AST::MethodCallStatementNode*>(statement));
            break;
        default:
            assert(false && "Unknown statement kind for lowering");
    }
}

void InstructionLowering::LowerFunction(ASTMethod* methodDefinition, Core::IR::Function* function) {
    _methodDefinition = methodDefinition;
    _function = function;

    // Create entry block and an IR Builder to use it
    IR::BasicBlock* entryBlock = function->CreateBlock("entry");
    IR::IRBuilder builder(entryBlock);
    _builder = &builder;

    // Convert any function parameters to local variables
    FunctionSymbolTable functionSymbolTable = CreateLocalVariables(methodDefinition);
    _functionSymbolTable = &functionSymbolTable;

    for (AST::StatementNode* statement : methodDefinition->MethodDecl->Statements) {
        LowerStatement(statement);
    }
    LowerReturnExpression(methodDefinition->MethodDecl->ReturnExp);

    // clear state variables
    _methodDefinition = nullptr;
    _function = nullptr;
    _builder = nullptr;
    _functionSymbolTable = nullptr;
}


}} // end namespace