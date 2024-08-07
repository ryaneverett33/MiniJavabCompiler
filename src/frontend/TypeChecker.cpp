#include "minijavab/frontend/TypeChecker.h"

#include <cassert>

namespace MiniJavab {
namespace Frontend {
namespace TypeChecker {

struct TypeCheckProcedure {
    TypeCheckProcedure(ASTClassTable* const table, std::ostream& errs)
        : Table(table),
        Errs(errs) {}

    AST::Type* FatalError(std::string message);
    AST::Type* GetType(AST::BinaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::IndexExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::LengthExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::LiteralExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::MethodCallExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::ObjectExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::UnaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    AST::Type* GetType(AST::ExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::AssignmentStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::IfStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::PrintStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::ReturnStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::WhileStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::StatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    void TypeCheck(AST::MethodDeclNode* const node, ASTClass* const classObject);
    void TypeCheck(AST::ClassDeclNode* const node);

    void Resolve(AST::AssignmentStatementNode* const node);

    void Resolve(AST::LengthExpNode* const node);
    void Resolve(AST::IndexExpNode* const node);
    void Resolve(AST::MethodCallExpNode* const node);
    void Resolve(AST::ObjectExpNode* const node);

    void Resolve(AST::ExpNode* const node, ASTMethod* const parentMethod);
    void Resolve(AST::StatementNode* const node, ASTMethod* const parentMethod);
    void Resolve(AST::ClassDeclNode* const node);

    void Error(std::string message);

    ASTClassTable* const Table;
    std::ostream& Errs;
    bool ValidCheck = true;
};

ASTVariable* findVariableOrParameter(std::string name, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (ASTVariable* parameter = methodObject->GetParameter(name)) {
        return parameter;
    }
    else if (ASTVariable* localVariable = methodObject->GetVariable(name)) {
        return localVariable;
    }
    else if (ASTVariable* classVariable = classObject->GetVariable(name)) {
        return classVariable;
    }
    return nullptr;
}

ASTVariable* findVariableSymbol(std::string name, ASTMethod* const containingMethod) {
    // check for symbol existence by parameter, variable, class variable
    if (ASTVariable* parameter = containingMethod->GetParameter(name)) {
        return parameter;
    }
    else if (ASTVariable* functionVariable = containingMethod->GetVariable(name)) {
        return functionVariable;
    }
    else if (ASTVariable* classVariable = containingMethod->ParentClass->GetVariable(name)) {
        return classVariable;
    }
    return nullptr;
}



AST::Type* TypeCheckProcedure::FatalError(std::string message) {
    ValidCheck = false;
    Errs << message << "\n";
    return nullptr;
}

void TypeCheckProcedure::Resolve(AST::LengthExpNode* const node) {    
    ASTVariable* symbol = findVariableSymbol(node->Name, node->ParentMethod);
    if (symbol == nullptr) {
        FatalError("cannot find symbol: '" + node->Name + "'");
        return;
    }

    node->ObjectInfo = symbol;
}

void TypeCheckProcedure::Resolve(AST::IndexExpNode* const node) {
    ASTVariable* symbol = findVariableSymbol(node->Object, node->ParentMethod);
    if (symbol == nullptr) {
        FatalError("cannot find symbol: '" + node->Object + "'");
        return;
    }

    node->ObjectInfo = symbol;
}

void TypeCheckProcedure::Resolve(AST::MethodCallExpNode* const node) {
    ASTClass* objectClass = node->Object->ClassInfo;

    // Resolve the class information of the symbol we're calling (if it hasn't already been found)
    if (objectClass == nullptr) {
        if (node->Object->IsThisObject()) {
            objectClass = node->ParentMethod->ParentClass;
        }
        else if (node->Object->IsNamedObject()) {
            AST::NamedObjectNode* namedObject = static_cast<AST::NamedObjectNode*>(node->Object);
            if (node->Object->ClassInfo == nullptr) {
                if (namedObject->IsNewObject()) {
                    AST::NewObjectNode* newObject = static_cast<AST::NewObjectNode*>(namedObject);
                    newObject->ClassInfo = Table->GetClass(newObject->Name);
                    if (newObject->ClassInfo == nullptr) {
                        FatalError("cannot find class: '" + newObject->Name + "'");;
                        return;
                    }

                    objectClass = newObject->ClassInfo;
                }
                else {
                    ASTVariable* objectSymbol = findVariableSymbol(namedObject->Name, node->ParentMethod);
                    if (objectSymbol == nullptr) {
                        FatalError("cannot find symbol: '" + namedObject->Name + "'");
                        return;
                    }

                    if (!objectSymbol->IsObjectType()) {
                        FatalError("cannot find symbol: method '" + node->Method + '"');
                        return;
                    }

                    objectClass = objectSymbol->ClassInfo;
                    namedObject->Symbol = objectSymbol;
                }
            }
        }
        else {
            FatalError("cannot invoke method on an array type");
            return;
        }
    }

    // Store away the class info of the symbol if it hasn't already been found
    if (node->Object->ClassInfo == nullptr) {
        node->Object->ClassInfo = objectClass;
    }

    // Find the method being called and stash it away
    node->CalledMethod = objectClass->GetMethod(node->Method);
    if (node->CalledMethod == nullptr) {
        FatalError("cannot find symbol: method '" + node->Method + "'");
        return;
    }
}

void TypeCheckProcedure::Resolve(AST::ObjectExpNode* const node) {
    if (node->Object->IsThisObject()) {
        AST::ThisObjectNode* thisObject = static_cast<AST::ThisObjectNode*>(node->Object);
        if (thisObject->ClassInfo == nullptr) {
            thisObject->ClassInfo = node->ParentMethod->ParentClass;
        }
    }
    else if (node->Object->IsNamedObject()) {
        AST::NamedObjectNode* namedObject = static_cast<AST::NamedObjectNode*>(node->Object);

        if (namedObject->ClassInfo == nullptr) {
            // NOTE: same logic as MethodCall resolution
            if (namedObject->IsNewObject()) {
                AST::NewObjectNode* newObject = static_cast<AST::NewObjectNode*>(namedObject);
                newObject->ClassInfo = Table->GetClass(namedObject->Name);
                if (newObject->ClassInfo == nullptr) {
                    FatalError("cannot find class: '" + newObject->Name + "'");;
                    return;
                }
            }
            else {
                ASTVariable* objectSymbol = findVariableSymbol(namedObject->Name, node->ParentMethod);
                if (objectSymbol == nullptr) {
                    FatalError("cannot find symbol: '" + namedObject->Name + "'");
                    return;
                }

                namedObject->ClassInfo = objectSymbol->ParentClass;
                namedObject->Symbol = objectSymbol;
            }
        }
    }
    else if (node->Object->IsNewArray()) {
        // do nothing, there is nothing to resolve
    }
}

void TypeCheckProcedure::Resolve(AST::ExpNode* const node, ASTMethod* const parentMethod) {
    node->ParentMethod = parentMethod;

    switch (node->Kind) {
        case AST::ExpKind::Binary: {
            AST::BinaryExpNode* binaryExpression = static_cast<AST::BinaryExpNode*>(node);
            Resolve(binaryExpression->LeftSide, parentMethod);
            Resolve(binaryExpression->RightSide, parentMethod);
            break;
        }
        case AST::ExpKind::Index: {
            Resolve(static_cast<AST::IndexExpNode*>(node));
            break;
        }
        case AST::ExpKind::LengthMethod: {
            Resolve(static_cast<AST::LengthExpNode*>(node));
            break;
        }

        case AST::ExpKind::MethodCall: {
            Resolve(static_cast<AST::MethodCallExpNode*>(node));
            break;
        }
        case AST::ExpKind::Nested: {
            AST::NestedExpNode* nestedExpression = static_cast<AST::NestedExpNode*>(node);
            Resolve(nestedExpression->Expression, parentMethod);
            break;
        }
        case AST::ExpKind::Object: {
            Resolve(static_cast<AST::ObjectExpNode*>(node));
            break;
        }
        case AST::ExpKind::Unary: {
            AST::UnaryExpNode* unaryExpression = static_cast<AST::UnaryExpNode*>(node);
            Resolve(unaryExpression->Expression, parentMethod);
            break;
        }
        case AST::ExpKind::Literal:
            // do nothing
            break;
        default:
            assert(false && "unknown expression kind for symbol resolution");
    }
}

void TypeCheckProcedure::Resolve(AST::AssignmentStatementNode* const node) {
    Resolve(node->Expression, node->ParentMethod);
    
    ASTVariable* symbol = findVariableSymbol(node->Name, node->ParentMethod);
    if (symbol == nullptr) {
        FatalError("cannot find symbol: '" + node->Name + "'");
        return;
    }

    node->AssignedVariable = symbol;
}

void TypeCheckProcedure::Resolve(AST::StatementNode* const node, ASTMethod* const parentMethod) {
    node->ParentMethod = parentMethod;
    switch (node->Kind) {
        case AST::StatementKind::Assignment:
            Resolve(static_cast<AST::AssignmentStatementNode*>(node));
            break;
        case AST::StatementKind::If: {
            AST::IfStatementNode* const ifNode = static_cast<AST::IfStatementNode*>(node);
            Resolve(ifNode->IfStatement, parentMethod);
            Resolve(ifNode->ElseStatement, parentMethod);
            Resolve(ifNode->Expression, parentMethod);
            break;
        }
        case AST::StatementKind::Nested: {
            AST::NestedStatementsNode* const nestedStatements = static_cast<AST::NestedStatementsNode*>(node);
            for (AST::StatementNode* nestedStatement : nestedStatements->Statements) {
                Resolve(nestedStatement, parentMethod);
            }
            break;
        }
        case AST::StatementKind::Print: {
            AST::PrintStatementNode* printStatement = static_cast<AST::PrintStatementNode*>(node);
            Resolve(printStatement->Expression, parentMethod);
            break;
        }
        case AST::StatementKind::Return: {
            AST::ReturnStatementNode* const returnStatement = static_cast<AST::ReturnStatementNode*>(node);
            Resolve(returnStatement->Expression, parentMethod);
            break;
        }
        case AST::StatementKind::While: {
            AST::WhileStatementNode* const whileStatement = static_cast<AST::WhileStatementNode*>(node);
            Resolve(whileStatement->Statement, parentMethod);
            Resolve(whileStatement->Expression, parentMethod);
            break;
        }
        case AST::StatementKind::MethodCall: {
            AST::MethodCallStatementNode* const methodCall = static_cast<AST::MethodCallStatementNode*>(node);
            Resolve(methodCall->CallExpression, parentMethod);
            break;
        }
        default:
            assert(false && "unknown statement kind for symbol resolution!");
    }
}

void TypeCheckProcedure::Resolve(AST::ClassDeclNode* const node) {
    ASTClass* classInfo = Table->GetClass(node->Name);
    assert(classInfo != nullptr && "Corrupted Symbol Table, can't find class");

    // Assign class info for the class
    node->ClassInfo = classInfo;

    // Assign variable info for each variable
    for (AST::VarDeclNode* const classVariable: node->Variables) {
        classVariable->VariableInfo = classInfo->GetVariable(classVariable->Name);
        assert(classVariable->VariableInfo != nullptr && "Corrupted Symbol Table, can't find class variable");
    }

    // Assign method info for each method and then perform resolution for references within the method
    for (AST::MethodDeclNode* const classMethod: node->Methods) {
        classMethod->MethodInfo = classInfo->GetMethod(classMethod->Name);
        assert(classMethod->MethodInfo != nullptr && "Corrupted Symbol Table, can't find class method");

        // Assign variable information for each parameter and declared variable
        for (AST::VarDeclNode* const methodParameter: classMethod->Parameters) {
            methodParameter->VariableInfo = classMethod->MethodInfo->GetParameter(methodParameter->Name);
            assert(methodParameter->VariableInfo != nullptr && "Corrupted Symbol Table, can't find method parameter");
        } 
        for (AST::VarDeclNode* const methodVariable: classMethod->Variables) {
            methodVariable->VariableInfo = classMethod->MethodInfo->GetVariable(methodVariable->Name);
            assert(methodVariable->VariableInfo != nullptr && "Corrupted Symbol Table, can't find method variable");
        }

        // Perform symbol resolution for each statement and return expression
        for (AST::StatementNode* const statement: classMethod->Statements) {
            Resolve(statement, classMethod->MethodInfo);
        }
        if (classMethod->ReturnExp != nullptr) {
            Resolve(classMethod->ReturnExp, classMethod->MethodInfo);
        }
    }
}

AST::Type* TypeCheckProcedure::GetType(AST::BinaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType != std::nullopt) {
        return *(node->ExpressionType);
    }
    
    AST::Type* lhsType = GetType(node->LeftSide, classObject, methodObject);
    AST::Type* rhsType = GetType(node->RightSide, classObject, methodObject);
    if (lhsType == nullptr) {
        return FatalError("Failed to get Left Hand Side type");
    }
    if (rhsType == nullptr) {
        return FatalError("Failed to get Right Hand Side type");
    }

    switch (node->Operator) {
        // boolean -> boolean operations
        case AST::OperatorType::BooleanAnd: 
        case AST::OperatorType::BooleanOr: {
            if (!lhsType->IsBooleanType()) {
                return FatalError("Left Hand Side must be a boolean expression");
            }
            if (!rhsType->IsBooleanType()) {
                return FatalError("Right Hand Side must be a boolean expression");
            }
            node->ExpressionType = lhsType;
            return *(node->ExpressionType);
        }
        // int|boolean -> boolean operations
        case AST::OperatorType::EqualTo:
        case AST::OperatorType::NotEqualTo: {
            if ((!lhsType->IsBooleanType() && !rhsType->IsBooleanType()) &&
                (!lhsType->IsIntegerType() && !rhsType->IsIntegerType())) {
                return FatalError("Both sides of the binary expression must be the same type");
            }
            node->ExpressionType = new AST::BooleanType();
            return *(node->ExpressionType);
        }
        // int -> boolean operations
        case AST::OperatorType::LessThan:
        case AST::OperatorType::GreaterThan:
        case AST::OperatorType::LessThanEqualTo:
        case AST::OperatorType::GreaterThanEqualTo: {
            if (!lhsType->IsIntegerType()) {
                return FatalError("Left Hand Side must be a integer expression");
            }
            if (!rhsType->IsIntegerType()) {
                return FatalError("Right Hand Side must be a integer expression");
            }
            node->ExpressionType = new AST::BooleanType();
            return *(node->ExpressionType);
        }
        // int -> int operations
        case AST::OperatorType::Add:
        case AST::OperatorType::Subtract:
        case AST::OperatorType::Multiply:
        case AST::OperatorType::Divide: {
            if (!lhsType->IsIntegerType()) {
                return FatalError("Left Hand Side must be a integer expression");
            }
            if (!rhsType->IsIntegerType()) {
                return FatalError("Right Hand Side must be a integer expression");
            }
            node->ExpressionType = lhsType;
            return *(node->ExpressionType);
        };
        default: {
            return FatalError("Unknown binary operator");
        }
    }
}
AST::Type* TypeCheckProcedure::GetType(AST::IndexExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType != std::nullopt) {
        return *(node->ExpressionType);
    }
   
    ASTVariable* variable = node->ObjectInfo;

    // make sure the variable is an array type
    if (!variable->Type->IsArrayType()) {
        return FatalError("Cannot use an array operator on a non-array type");
    }

    // make sure the accessor indices are <= to the type dimensions 
    AST::ArrayType* variableType = static_cast<AST::ArrayType*>(variable->Type);
    if (node->Index->Expressions.size() > variableType->Dimensions) {
        return FatalError("Cannot access " + std::to_string(node->Index->Expressions.size()) + " dimensions of a " + std::to_string(variableType->Dimensions) + " dimensional array");
    }

    // if the accessor indices count matches the array dimensions, then we're accessing the base type (eg. arr[0] of int[] arr)
    if (node->Index->Expressions.size() == variableType->Dimensions) {
        node->ExpressionType = variableType->BaseType;
    }
    else { // else we're accessing a sub-array within the array (eg. arr[0] of int[][] arr)
        node->ExpressionType = new AST::ArrayType(variableType->BaseType, node->Index->Expressions.size());
    }
    return *(node->ExpressionType);
}
AST::Type* TypeCheckProcedure::GetType(AST::LengthExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType == std::nullopt) {
        ASTVariable* parameter = node->ObjectInfo;
        if (!parameter->Type->IsArrayType()) {
            return FatalError("Can't use the \".length\" method on a non-array type: " + node->Name);
        }
        node->ExpressionType = new AST::IntegerType();
    }
    return *(node->ExpressionType);
}
AST::Type* TypeCheckProcedure::GetType(AST::LiteralExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType != std::nullopt) {
        return *(node->ExpressionType);
    }

    if (node->IsIntegerLiteral()) {
        node->ExpressionType = new AST::IntegerType();
        return *(node->ExpressionType);
    }
    else if (node->IsBooleanLiteral()) {
        node->ExpressionType = new AST::BooleanType();
        return *(node->ExpressionType);
    }
    else if (node->IsStringLiteral()) {
        node->ExpressionType = new AST::StringType();
        return *(node->ExpressionType);
    }

    assert(false && "Unrecognized literal type");
}
AST::Type* TypeCheckProcedure::GetType(AST::MethodCallExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType != std::nullopt) {
        return *(node->ExpressionType);
    }
    
    // load the class information for the object being called
    if (node->Object->IsNewArray()) {
        // TODO implement
        assert(false && "typechecking for arrays not supported yet");
    }
    ASTClass* calledObject = node->Object->ClassInfo;

    // verify the method exists on the class
    ASTMethod* calledMethodObject = calledObject->GetMethod(node->Method);
    if (calledMethodObject == nullptr) {
        return FatalError("Method does not exist: " + node->Method);
    }
    node->CalledMethod = calledMethodObject;

    // TODO make sure the arguments passed to the method are correct
    node->ExpressionType = calledMethodObject->ReturnType;
    return *(node->ExpressionType);
}
AST::Type* TypeCheckProcedure::GetType(AST::ObjectExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType != std::nullopt) {
        return *(node->ExpressionType);
    }
    AST::ObjectNode* objectNode = node->Object;
    if (objectNode->IsNewArray()) {
        AST::NewArrayObjectNode* newArrayNode = static_cast<AST::NewArrayObjectNode*>(objectNode);
        size_t dimensions = newArrayNode->Index->Expressions.size();
        if (newArrayNode->Type->IsBooleanType()) {
            node->ExpressionType = new AST::ArrayType(new AST::BooleanType(), dimensions);
            return *(node->ExpressionType);
        }
        else if (newArrayNode->Type->IsIntegerType()) {
            node->ExpressionType = new AST::ArrayType(new AST::IntegerType(), dimensions);
            return *(node->ExpressionType);
        }
        else if (newArrayNode->Type->IsStringType()) {
            node->ExpressionType = new AST::ArrayType(new AST::StringType(), dimensions);
            return *(node->ExpressionType);
        }
        else if (newArrayNode->Type->IsObjectType()) {
            AST::ObjectTypeNode* objectType = static_cast<AST::ObjectTypeNode*>(newArrayNode->Type);
            node->ExpressionType = new AST::ArrayType(new AST::ObjectType(objectType->ObjectType), dimensions);
            return *(node->ExpressionType);
        }
        else {
            return FatalError("Cannot construct an array of this type");
        }
    }
    else if (objectNode->IsNamedObject()) {
        AST::NamedObjectNode* namedObject = static_cast<AST::NamedObjectNode*>(objectNode);
        if (namedObject->IsNewObject()) {
            node->ExpressionType = objectNode->ClassInfo->Type;
            return *(node->ExpressionType);
        }
        else {
            node->ExpressionType = static_cast<AST::NamedObjectNode*>(objectNode)->Symbol->Type;
            return *(node->ExpressionType);
        }
    }
    else {
        assert(false && "it happened");
        node->ExpressionType = objectNode->ClassInfo->Type;
        return *(node->ExpressionType);
    }
}
AST::Type* TypeCheckProcedure::GetType(AST::UnaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    AST::Type* type = GetType(node->Expression, classObject, methodObject);
    switch (node->Operator) {
        case AST::OperatorType::Add:
            if (!type->IsIntegerType()) {
                return FatalError("Unary Add operations only accept integers");
            }
            break;
        case AST::OperatorType::Subtract:
            if (!type->IsIntegerType()) {
                return FatalError("Unary Subtract operations only accept integers");
            }
            break;
        case AST::OperatorType::BooleanNot: {
            if (!type->IsBooleanType()) {
                return FatalError("Not operations only accept booleans");
            }
            break;
        }
        default:
            return FatalError("Unknown unary operator");
    }
    return type;
}

void TypeCheckProcedure::TypeCheck(AST::AssignmentStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    AST::Type* variableType = node->AssignedVariable->Type;

    // get the type of the expression
    AST::Type* expressionType = GetType(node->Expression, classObject, methodObject);
    if (expressionType == nullptr) {
        FatalError("Failed to get expression type for assignment statement");
        return;
    }

    // verify the types match
    if (node->IsIndexedAssignment()) {
        // find variable type
        AST::Type* variableType = nullptr;
        if (ASTVariable* parameter = methodObject->GetParameter(node->Name)) {
            variableType = parameter->Type;
        }
        else if (ASTVariable* methodVariable = methodObject->GetVariable(node->Name)) {
            variableType = methodVariable->Type;
        }
        else if (ASTVariable* objectVariable = classObject->GetVariable(node->Name)) {
            variableType = objectVariable->Type;
        }
        else {
            FatalError("Variable " + node->Name + " does not exist");
            return;
        }

        if (!variableType->IsArrayType()) {
            FatalError("Cannot use " + node->Name + " as an array");
            return;
        }

        // get expression type
        AST::Type* expressionType = GetType(node->Expression, classObject, methodObject);
        if (expressionType == nullptr) {
            FatalError("Failed to get type of assignment expression");
            return;
        }

        // verify types match
        // TODO verify assigning to a lower dimension in a multi dimensional array
        AST::ArrayType* variableArrayType = static_cast<AST::ArrayType*>(variableType);
        if (!expressionType->Equals(variableArrayType->BaseType)) {
            FatalError("Type mismatch");
            return;
        }
    }
    else {
        if (!variableType->Equals(expressionType)) {
            FatalError("Assignment statement type mismatch");
        }
    }
}

void TypeCheckProcedure::TypeCheck(AST::IfStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // type of the expression must be a boolean type
    AST::Type* conditionalType = GetType(node->Expression, classObject, methodObject);
    if (conditionalType == nullptr) {
        FatalError("Failed to get type for if statement");
    }
    else {
        if (!conditionalType->IsBooleanType()) {
            FatalError("If Statement must be a boolean type");
        } 
    }

    // typecheck the statements
    TypeCheck(node->IfStatement, classObject, methodObject);
    TypeCheck(node->ElseStatement, classObject, methodObject);
}

void TypeCheckProcedure::TypeCheck(AST::PrintStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // we only need to check the type of Print(expression) because Print(string) is always the correct type
    AST::Type* expressionType = GetType(node->Expression, classObject, methodObject);
    if (expressionType == nullptr) { 
        FatalError("Failed to get expression type");
        return; 
    }
    // print statements accepts literals or integer expressions
    if (node->Expression->IsLiteralExpression()) {
        if (!expressionType->IsIntegerType() && !expressionType->IsStringType()) {
            FatalError("Print expression only accepts integer and string literals");
        }
    }
    else if (!expressionType->IsIntegerType()) {
        FatalError("Print expression must return an integer");
    }
}

void TypeCheckProcedure::TypeCheck(AST::ReturnStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // verify the type of the return expression is the same as the method body
    AST::Type* expressionType = GetType(node->Expression, classObject, methodObject);
    if (expressionType == nullptr) {
        FatalError("Failed to get return expression type");
    }
    else {
        if (!expressionType->Equals(methodObject->ReturnType)) {
            FatalError("Return type mismatch!");
        }
    }
}

void TypeCheckProcedure::TypeCheck(AST::WhileStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // verify the type of the conditional expression is a boolean
    AST::Type* expressionType = GetType(node->Expression, classObject, methodObject);
    if (expressionType == nullptr) {
        FatalError("Failed to get conditional expression type");
    }
    else {
        if (!expressionType->IsBooleanType()) {
            FatalError("Conditional type must be a boolean!");
        }
    }

    // typecheck the statement body
    TypeCheck(node->Statement, classObject, methodObject);
}

AST::Type* TypeCheckProcedure::GetType(AST::ExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->IsBinaryExpression()) {
        return GetType(static_cast<AST::BinaryExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsIndexExpression()) {
        return GetType(static_cast<AST::IndexExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsLengthMethodExpression()) {
        return GetType(static_cast<AST::LengthExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsLiteralExpression()) {
        return GetType(static_cast<AST::LiteralExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsMethodCallExpression()) {
        return GetType(static_cast<AST::MethodCallExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsNestedExpression()) {
        AST::NestedExpNode* nestedNode = static_cast<AST::NestedExpNode*>(node);
        return GetType(nestedNode->Expression, classObject, methodObject);
    }
    else if (node->IsObjectExpression()) {
        return GetType(static_cast<AST::ObjectExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsUnaryExpression()) {
        return GetType(static_cast<AST::UnaryExpNode*>(node), classObject, methodObject);
    }
    else {
        assert(false && "Unrecognized expression type");
    }
    return nullptr;
}

void TypeCheckProcedure::TypeCheck(AST::StatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->IsAssignmentStatement()) {
        TypeCheck(static_cast<AST::AssignmentStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsIfStatement()) {
        TypeCheck(static_cast<AST::IfStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsNestedStatement()) {
        AST::NestedStatementsNode* nestedNode = static_cast<AST::NestedStatementsNode*>(node);
        for (AST::StatementNode* nestedStatement : nestedNode->Statements) {
            TypeCheck(nestedStatement, classObject, methodObject);
        }
    }
    else if (node->IsPrintStatement()) {
        TypeCheck(static_cast<AST::PrintStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsReturnStatement()) {
        TypeCheck(static_cast<AST::ReturnStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsWhileStatement()) {
        TypeCheck(static_cast<AST::WhileStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsMethodCallStatement()) {
        AST::MethodCallStatementNode* callMethod = static_cast<AST::MethodCallStatementNode*>(node);
        GetType(callMethod->CallExpression, classObject, methodObject);
    }
    else {
        assert(false && "Non-recognized Statement Type");
    }
}

void TypeCheckProcedure::TypeCheck(AST::MethodDeclNode* const node, ASTClass* const classObject) {
    ASTMethod* methodObject = classObject->GetMethod(node->Name);
    for (AST::StatementNode* const statementNode: node->Statements) {
        TypeCheck(statementNode, classObject, methodObject);
    }

    // check if the return expression is the right type
    if (node->ReturnExp != nullptr) {
        AST::Type* returnType = GetType(node->ReturnExp, classObject, methodObject);

        if (returnType == nullptr) {
            FatalError("Failed to get return type");
            return;
        }

        if (!returnType->Equals(methodObject->ReturnType)) {
            FatalError("Return type doesn't match");
            return;
        } 
    }
    else {
        // if the return expression is null, then the method type must be void
        if (!methodObject->ReturnType->IsVoidType()) {
            FatalError("Method doesn't return for non-void type method");
            return;
        }
    }
}

void TypeCheckProcedure::TypeCheck(AST::ClassDeclNode* const node) {
    ASTClass* classObject = Table->GetClass(node->Name);
    for (AST::MethodDeclNode* const methodDecl: node->Methods) {
        TypeCheck(methodDecl, classObject);
    }
}

bool Check(AST::ProgramNode* const program, ASTClassTable* const table, std::ostream& errs) {
    if (table == nullptr) {
        return false;
    }
    TypeCheckProcedure typechecker(table, errs);

    // Step 1, resolve any symbolic references within the AST to make typechecking easier
    typechecker.Resolve(program->MainClass);
    for (AST::ClassDeclNode* const classDecl: program->Classes) {
        typechecker.Resolve(classDecl);
    }

    // Step 2, Perform typechecking on each class/method in the program
    typechecker.TypeCheck(program->MainClass);
    for (AST::ClassDeclNode* const classDecl: program->Classes) {
        typechecker.TypeCheck(classDecl);
    }
    
    return typechecker.ValidCheck;
}

}}} // end namespace