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

AST::Type* TypeCheckProcedure::FatalError(std::string message) {
    ValidCheck = false;
    Errs << message << "\n";
    return nullptr;
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
   
    // check that the variable exists
    ASTVariable* variable = nullptr;
    if (ASTVariable* parameter = methodObject->GetParameter(node->Object)) {
        variable = parameter;
    }
    else if (ASTVariable* methodVariable = methodObject->GetVariable(node->Object)) {
        variable = methodVariable;
    }
    else if (ASTVariable* objectVariable = classObject->GetVariable(node->Object)) {
        variable = objectVariable;
    }
    else {
        return FatalError("Variable doesn't exist: " + node->Object);
    }

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
        // lookup the object
        ASTVariable* parameter = findVariableOrParameter(node->Name, classObject, methodObject);
        if (parameter == nullptr) {
            return FatalError("Object does not exist: " + node->Name);
        }
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
    ASTClass* calledObject = nullptr;
    if (node->Object->IsThisObject()) {
        calledObject = classObject;
    }
    else if (node->Object->IsNewArray()) {
        // TODO implement
        assert(false && "typechecking for arrays not supported yet");
    }
    else if (node->Object->IsNamedObject()) {
        AST::NamedObjectNode* namedCalledObject = static_cast<AST::NamedObjectNode*>(node->Object);

        if (namedCalledObject->IsNewObject()) {
            AST::NewObjectNode* newObjectNode = dynamic_cast<AST::NewObjectNode*>(namedCalledObject);
            calledObject = Table->GetClass(newObjectNode->Name);
            if (calledObject == nullptr) {
                return FatalError("Not an object type: " + newObjectNode->Name);
            }
        }
        else {
            // object could either be a variable or a parameter somewhere, we have to find it (if it's valid)
            if (ASTVariable* parameter = methodObject->GetParameter(namedCalledObject->Name)) {
                if (!parameter->Type->IsObjectType()) {
                    return FatalError("Cannot invoke method on non-object type: " + namedCalledObject->Name);
                }
                AST::ObjectType* objType = dynamic_cast<AST::ObjectType*>(parameter->Type);
                calledObject = Table->GetClass(objType->TypeName);
                if (calledObject == nullptr) {
                    return FatalError("Parameter has invalid type: " + namedCalledObject->Name);
                }
            }
            else if (ASTVariable* methodVariable = methodObject->GetVariable(namedCalledObject->Name)) {
                if (!methodVariable->Type->IsObjectType()) {
                    return FatalError("Cannot invoke method on non-object type: " + namedCalledObject->Name);
                }
                AST::ObjectType* objType = dynamic_cast<AST::ObjectType*>(methodVariable->Type);
                calledObject = Table->GetClass(objType->TypeName);
                if (calledObject == nullptr) {
                    return FatalError("Method variable has invalid type: " + namedCalledObject->Name);
                }
            }
            else if (ASTVariable* classVariable = classObject->GetVariable(namedCalledObject->Name)) {
                if (!methodVariable->Type->IsObjectType()) {
                    return FatalError("Cannot invoke method on non-object type: " + namedCalledObject->Name);
                }
                AST::ObjectType* objType = dynamic_cast<AST::ObjectType*>(classVariable->Type);
                calledObject = Table->GetClass(objType->TypeName);
                if (calledObject == nullptr) {
                    return FatalError("Method variable has invalid type: " + namedCalledObject->Name);
                }
            }
            else {
                // if it's not a method parameter, method variable, or a class variable then it's not a valid object to invoke upon
                node->Dump();
                return FatalError("Object is not valid: " + namedCalledObject->Name);
            }
        }
    }
    else { assert(false && "Unrecognized object type"); }

    // verify the method exists on the class
    ASTMethod* calledMethodObject = calledObject->GetMethod(node->Method);
    if (calledMethodObject == nullptr) {
        return FatalError("Method does not exist: " + node->Method);
    }

    // TODO make sure the arguments passed to the method are correct
    node->ExpressionType = calledMethodObject->ReturnType;
    return *(node->ExpressionType);
}
AST::Type* TypeCheckProcedure::GetType(AST::ObjectExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->ExpressionType != std::nullopt) {
        return *(node->ExpressionType);
    }
    AST::ObjectNode* objectNode = node->Object;

    if (objectNode->IsNamedObject()) {
        AST::NamedObjectNode* namedObjectNode = dynamic_cast<AST::NamedObjectNode*>(objectNode);

        if (namedObjectNode->IsNewObject()) {
            // Verify the class exists
            ASTClass* classDefinition = Table->GetClass(namedObjectNode->Name);
            if (classDefinition == nullptr) {
                return FatalError("Cannot construct object of type \"" + namedObjectNode->Name + "\", class doesn't exist");
            }
            node->ExpressionType = new AST::ObjectType(classDefinition->Name);
            return *(node->ExpressionType);
        }
        else {
            ASTVariable* variable = findVariableOrParameter(namedObjectNode->Name, classObject, methodObject);
            // verify that the named class exists before accepting it's type
            if (variable == nullptr) {
                return FatalError("Not a valid object type: " + namedObjectNode->Name);
            }
            node->ExpressionType = variable->Type;
            return *(node->ExpressionType);
        }
    }
    else if (objectNode->IsThisObject()) {
        node->ExpressionType = new AST::ObjectType(classObject->Name);
        return *(node->ExpressionType);
    }
    else if (objectNode->IsNewArray()) {
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

    node->Dump();
    assert(false && "Unrecognized object expression type");
}
AST::Type* TypeCheckProcedure::GetType(AST::UnaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    return GetType(node->Expression, classObject, methodObject);
}

void TypeCheckProcedure::TypeCheck(AST::AssignmentStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // verify the variable exists
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
    if (node->IsPrintExpressionStatement()) {
        AST::PrintExpStatementNode* printExpNode = dynamic_cast<AST::PrintExpStatementNode*>(node);
        AST::Type* expressionType = GetType(printExpNode->Expression, classObject, methodObject);
        if (expressionType == nullptr) { 
            ValidCheck = false; 
            Errs << "Failed to get expression type\n";
            return; 
        }
        if (!expressionType->IsIntegerType()) {
            ValidCheck = false;
            Errs << "Print expression must return an integer\n";
        }
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
            Errs << "Failed to get return type\n";
            ValidCheck = false;
            return;
        }

        if (!returnType->Equals(methodObject->ReturnType)) {
            Errs << "Return type doesn't match\n";
            ValidCheck = false;
            return;
        } 
    }
    else {
        // if the return expression is null, then the method type must be void
        if (!methodObject->ReturnType->IsVoidType()) {
            Errs << "Method doesn't return for non-void type method\n";
            ValidCheck = false;
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
    TypeCheckProcedure typechecker(table, errs);

    typechecker.TypeCheck(program->MainClass);

    for (AST::ClassDeclNode* const classDecl: program->Classes) {
        typechecker.TypeCheck(classDecl);
    }
    
    return typechecker.ValidCheck;
}

}}} // end namespace