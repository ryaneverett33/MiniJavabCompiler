#include "minijavab/frontend/InstructionLowering.h"

#include "minijavab/frontend/PrimitiveTypes.h"
#include "minijavab/frontend/Converter.h"
#include "minijavab/frontend/ASTClassTable.h"

#include "minijavab/core/ir/Module.h"
#include "minijavab/core/ir/BasicBlock.h"
#include "minijavab/core/ir/IRBuilder.h"
#include "minijavab/core/ir/IntegerConstant.h"
#include "minijavab/core/ir/StringConstant.h"

using namespace MiniJavab::Core;

namespace MiniJavab {
namespace Frontend {

InstructionLowering::InstructionLowering(ASTConverter* converter)
                        : _converter(converter) {}

InstructionLowering::FunctionSymbolTable InstructionLowering::CreateLocalVariables(ASTMethod* methodDefinition) {
    FunctionSymbolTable functionSymbolTable;

    // Create local variables for each passed-in parameter
    for (auto& [parameterName, parameter] : methodDefinition->Parameters) {
        IR::Parameter* functionParameter = _builder->Block->ParentFunction->GetParameterByName(parameterName);

        // Create a new local variable as a copy of the passed-in parameter
        IR::Value* localVariable = _builder->CreateAlloc(_converter->ResolveASTType(parameter->Type),
                                                            parameterName + ".local");
        
        // Store the passed-in parameter into the local variable
        _builder->CreateStore(functionParameter, localVariable);

        // Create two symbol table entries, one for the passed-in parameter and one for the copy
        FunctionSymbolEntry* localEntry = new FunctionSymbolEntry {
            /*Value*/ localVariable,
            /*isParameter*/ false,
            /*copiedSymbol*/ nullptr
        };

        FunctionSymbolEntry* parameterEntry = new FunctionSymbolEntry {
            /*Value*/ functionParameter,
            /*isParameter*/ true,
            /*copiedSymbol*/ localEntry
        };

        functionSymbolTable.insert({localVariable->Name, localEntry});
        functionSymbolTable.insert({parameterName, parameterEntry});
    }

    // Create local variables for each variable declaration in the method
    for (auto& [variableName, variable] : methodDefinition->Variables) {
        IR::Value* localVariable = _builder->CreateAlloc(_converter->ResolveASTType(variable->Type),
                                                            variableName);

        functionSymbolTable.insert({variableName, new FunctionSymbolEntry {
            /*Value*/ localVariable,
            /*isParameter*/ false,
            /*copiedSymbol*/ nullptr
        }});
    }

    return functionSymbolTable;
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
    IR::Value* leftHandSide = LowerExpression(expression->LeftSide);
    IR::Value* rightHandSide = LowerExpression(expression->RightSide);
    
    _builder->Block->ParentFunction->Dump();
    assert(false ** "binary expression lowering not implemented yet");
}

IR::Value* InstructionLowering::LowerExpression(AST::ObjectExpNode* expression) {
    assert(expression->Object->IsNamedObject() && "only named object expressions supported");

    if (expression->Object->IsNamedObject()) {
        AST::NamedObjectNode* namedObject = static_cast<AST::NamedObjectNode*>(expression->Object);
        // look up the symbol being assigned to
        // TODO: symbol finding needs to be redone
        IR::Value* symbol;
        FunctionSymbolTable::iterator search = _functionSymbolTable->find(namedObject->Name);
        if (search != _functionSymbolTable->end()) {
            symbol = (search->second->isParameter ? search->second->copiedSymbol->Value : search->second->Value);
        }

        return _builder->CreateLoad(static_cast<IR::PointerType*>(symbol->ValueType)->ElementType, symbol);
    }
    assert(false && "object expression not supported yet");
}

IR::Value* InstructionLowering::LowerExpression(AST::ExpNode* expression) {
    switch (expression->Kind) {
        case AST::ExpKind::Literal:
            return LowerExpression(static_cast<AST::LiteralExpNode*>(expression));
        case AST::ExpKind::Binary:
            return LowerExpression(static_cast<AST::BinaryExpNode*>(expression));
        case AST::ExpKind::Object:
            return LowerExpression(static_cast<AST::ObjectExpNode*>(expression));
        default:
            _builder->Block->ParentFunction->Dump();
            assert(false && "expression lowering not implemented yet");
    }
}

void InstructionLowering::LowerStatement(AST::AssignmentStatementNode* statement) {
    assert(!statement->IsIndexedAssignment() && "indexed assignment not supported yet");

    // look up the symbol being assigned to
    // TODO: symbol finding needs to be redone
    IR::Value* symbol;
    FunctionSymbolTable::iterator search = _functionSymbolTable->find(statement->Name);
    if (search != _functionSymbolTable->end()) {
        symbol = (search->second->isParameter ? search->second->copiedSymbol->Value : search->second->Value);
    }
    
    IR::Value* assignmentValue = LowerExpression(statement->Expression);
    _builder->CreateStore(assignmentValue, symbol);
}
void InstructionLowering::LowerStatement(AST::IfStatementNode* statement) {
    assert(false && "if statement lowering ot implemented yet");
}
void InstructionLowering::LowerStatement(AST::NestedStatementsNode* statement) {
    assert(false && "nested lowering ot implemented yet");
}
void InstructionLowering::LowerStatement(AST::PrintStatementNode* statement) {
    if (statement->IsPrintStringStatement()) {
        AST::PrintStringStatementNode* stringStatement = static_cast<AST::PrintStringStatementNode*>(statement);

        // Create a new global variable storing the string to print
        IR::Module* mod = _function->GetContainingModule();
        IR::GlobalVariable* constant = mod->AddStringConstant(stringStatement->String);

        // Call the print intrinsic with a pointer to the global string
        IR::Value* stringPointer = _builder->CreateGetPtr(constant);
        IR::Function* printFunction = mod->GetIntrinsic(IR::MJ_PRINTLN_STR_INTRINSIC);
        _builder->CreateCall(printFunction, {stringPointer});
    }
    else {
        AST::PrintExpStatementNode* expStatement = static_cast<AST::PrintExpStatementNode*>(statement);
        assert(false && "print expression statement lowering not implemented yet");
    }
}
void InstructionLowering::LowerStatement(AST::ReturnStatementNode* statement) {
    assert(false && "return statement lowering ot implemented yet");
}
void InstructionLowering::LowerStatement(AST::WhileStatementNode* statement) {
    assert(false && "while statement lowering ot implemented yet");
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
    if (methodDefinition->MethodDecl->ReturnExp != nullptr) {
        methodDefinition->MethodDecl->ReturnExp->Dump();
    }

    // clear state variables
    _methodDefinition = nullptr;
    _function = nullptr;
    _builder = nullptr;
    _functionSymbolTable = nullptr;
}


}} // end namespace