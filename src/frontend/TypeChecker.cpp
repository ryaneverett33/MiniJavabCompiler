#include "TypeChecker.h"

namespace MiniJavab {
namespace Frontend {
namespace TypeChecker {

struct TypeCheckProcedure {
    TypeCheckProcedure(ASTClassTable* const table, std::ostream& errs)
        : Table(table),
        Errs(errs) {}

    Core::Type* FatalError(std::string message);
    Core::Type* GetType(AST::BinaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::IndexExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::LengthExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::LiteralExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::MethodCallExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::ObjectExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::UnaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
    Core::Type* GetType(AST::ExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject);
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

Core::Type* TypeCheckProcedure::FatalError(std::string message) {
    ValidCheck = false;
    Errs << message << std::endl;
    return nullptr;
}
Core::Type* TypeCheckProcedure::GetType(AST::BinaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    return nullptr;
}
Core::Type* TypeCheckProcedure::GetType(AST::IndexExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    return nullptr;
}
Core::Type* TypeCheckProcedure::GetType(AST::LengthExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // lookup the object
    ASTVariable* parameter = findVariableOrParameter(node->Name, classObject, methodObject);
    if (parameter == nullptr) {
        return FatalError("Object does not exist: " + node->Name);
    }
    if (!parameter->Type->IsArrayType()) {
        return FatalError("Can't use the \".length\" method on a non-array type: " + node->Name);
    }
    return new Core::IntegerType();
}
Core::Type* TypeCheckProcedure::GetType(AST::LiteralExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->IsIntegerLiteral()) {
        return new Core::IntegerType();
    }
    else if (node->IsBooleanLiteral()) {
        return new Core::BooleanType();
    }
    else if (node->IsStringLiteral()) {
        return new Core::StringType();
    }

    assert(false && "Unrecognized literal type");
}
Core::Type* TypeCheckProcedure::GetType(AST::MethodCallExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
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
                Core::ObjectType* objType = dynamic_cast<Core::ObjectType*>(parameter->Type);
                calledObject = Table->GetClass(objType->TypeName);
                if (calledObject == nullptr) {
                    return FatalError("Parameter has invalid type: " + namedCalledObject->Name);
                }
            }
            else if (ASTVariable* methodVariable = methodObject->GetVariable(namedCalledObject->Name)) {
                if (!methodVariable->Type->IsObjectType()) {
                    return FatalError("Cannot invoke method on non-object type: " + namedCalledObject->Name);
                }
                Core::ObjectType* objType = dynamic_cast<Core::ObjectType*>(methodVariable->Type);
                calledObject = Table->GetClass(objType->TypeName);
                if (calledObject == nullptr) {
                    return FatalError("Method variable has invalid type: " + namedCalledObject->Name);
                }
            }
            else if (ASTVariable* classVariable = classObject->GetVariable(namedCalledObject->Name)) {
                if (!methodVariable->Type->IsObjectType()) {
                    return FatalError("Cannot invoke method on non-object type: " + namedCalledObject->Name);
                }
                Core::ObjectType* objType = dynamic_cast<Core::ObjectType*>(classVariable->Type);
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
    return calledMethodObject->ReturnType;
}
Core::Type* TypeCheckProcedure::GetType(AST::ObjectExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    AST::ObjectNode* objectNode = node->Object;

    if (objectNode->IsNamedObject()) {
        AST::NamedObjectNode* namedObjectNode = dynamic_cast<AST::NamedObjectNode*>(objectNode);

        ASTVariable* variable = findVariableOrParameter(namedObjectNode->Name, classObject, methodObject);
        // verify that the named class exists before accepting it's type
        if (variable == nullptr) {
            ValidCheck = false;
            Errs << "Not a valid object type: " << namedObjectNode->Name << std::endl;
            return nullptr;
        }
        return variable->Type;
    }
    else if (objectNode->IsThisObject()) {
        return new Core::ObjectType(classObject->Name);
    }

    assert(false && "Unrecognized object expression type");
}
Core::Type* TypeCheckProcedure::GetType(AST::UnaryExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    return nullptr;
}

void TypeCheckProcedure::TypeCheck(AST::AssignmentStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
}

void TypeCheckProcedure::TypeCheck(AST::IfStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
}

void TypeCheckProcedure::TypeCheck(AST::PrintStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    // we only need to check the type of Print(expression) because Print(string) is always the correct type
    if (node->IsPrintExpressionStatement()) {
        AST::PrintExpStatementNode* printExpNode = dynamic_cast<AST::PrintExpStatementNode*>(node);
        Core::Type* expressionType = GetType(printExpNode->Expression, classObject, methodObject);
        if (expressionType == nullptr) { ValidCheck = false; return; }
        if (!expressionType->IsIntegerType()) {
            ValidCheck = false;
            Errs << "Print expression must return an integer" << std::endl;
        }
    }
}

void TypeCheckProcedure::TypeCheck(AST::ReturnStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
}

void TypeCheckProcedure::TypeCheck(AST::WhileStatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
}

Core::Type* TypeCheckProcedure::GetType(AST::ExpNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->IsBinaryExpression()) {
        return GetType(dynamic_cast<AST::BinaryExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsIndexExpression()) {
        return GetType(dynamic_cast<AST::IndexExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsLengthMethodExpression()) {
        return GetType(dynamic_cast<AST::LengthExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsLiteralExpression()) {
        return GetType(dynamic_cast<AST::LiteralExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsMethodCallExpression()) {
        return GetType(dynamic_cast<AST::MethodCallExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsNestedExpression()) {
        AST::NestedExpNode* nestedNode = dynamic_cast<AST::NestedExpNode*>(node);
        return GetType(nestedNode->Expression, classObject, methodObject);
    }
    else if (node->IsObjectExpression()) {
        return GetType(dynamic_cast<AST::ObjectExpNode*>(node), classObject, methodObject);
    }
    else if (node->IsUnaryExpression()) {
        return GetType(dynamic_cast<AST::UnaryExpNode*>(node), classObject, methodObject);
    }
    else {
        assert(false && "Unrecognized expression type");
    }
    return nullptr;
}

void TypeCheckProcedure::TypeCheck(AST::StatementNode* const node, ASTClass* const classObject, ASTMethod* const methodObject) {
    if (node->IsAssignmentStatement()) {
        TypeCheck(dynamic_cast<AST::AssignmentStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsIfStatement()) {
        TypeCheck(dynamic_cast<AST::IfStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsNestedStatement()) {
        AST::NestedStatementsNode* nestedNode = dynamic_cast<AST::NestedStatementsNode*>(node);
        for (AST::StatementNode* nestedStatement : nestedNode->Statements) {
            TypeCheck(nestedStatement, classObject, methodObject);
        }
    }
    else if (node->IsPrintStatement()) {
        TypeCheck(dynamic_cast<AST::PrintStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsReturnStatement()) {
        TypeCheck(dynamic_cast<AST::ReturnStatementNode*>(node), classObject, methodObject);
    }
    else if (node->IsWhileStatement()) {
        TypeCheck(dynamic_cast<AST::WhileStatementNode*>(node), classObject, methodObject);
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
        Core::Type* returnType = GetType(node->ReturnExp, classObject, methodObject);

        if (returnType == nullptr) {
            Errs << "Failed to get return type" << std::endl;
            ValidCheck = false;
            return;
        }

        if (!returnType->Equals(methodObject->ReturnType)) {
            Errs << "Return type doesn't match" << std::endl;
            ValidCheck = false;
            return;
        } 
    }
    else {
        // if the return expression is null, then the method type must be void
        if (!methodObject->ReturnType->IsVoidType()) {
            Errs << "Method doesn't return for non-void type method" << std::endl;
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