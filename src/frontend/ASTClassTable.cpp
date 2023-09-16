#include "minijavab/frontend/ASTClassTable.h"
#include "minijavab/frontend/frontend.h"

namespace MiniJavab {
namespace Frontend {

ASTVariable::ASTVariable(AST::VarDeclNode* varDecl)
    : VarDecl(varDecl)
{
    Name = varDecl->Name;
    Type = ConvertTypeNodeToType(varDecl->Type);
}

ASTMethod::ASTMethod(AST::MethodDeclNode* methodDecl)
    : MethodDecl(methodDecl)
{
    Name = methodDecl->Name;
    ReturnType = ConvertTypeNodeToType(methodDecl->Type);

    // load variable info by examining the MethodDeclNode's variable list
    for (AST::VarDeclNode* variableDecl: methodDecl->Variables) {
        ASTVariable* variable = new ASTVariable(variableDecl);
        Variables.insert({variable->Name, variable});
    }

    // load parameter info from the node's method list
    for (AST::VarDeclNode* parameterDecl: methodDecl->Parameters) {
        ASTVariable* parameter = new ASTVariable(parameterDecl);
        Parameters.insert({parameter->Name, parameter});
    }
}

ASTVariable* ASTMethod::GetVariable(std::string variableName) {
    auto lookupResult = Variables.find(variableName);
    return lookupResult != Variables.end() ?
                lookupResult->second :
                nullptr;
}

ASTVariable* ASTMethod::GetParameter(std::string parameterName) {
    auto lookupResult = Parameters.find(parameterName);
    return lookupResult != Parameters.end() ?
                lookupResult->second :
                nullptr;
}

ASTClass::ASTClass(AST::ClassDeclNode* classDecl)
    : ClassDecl(classDecl),
    BaseClass(nullptr),
    IsExtensionClass(false)
{
    Name = classDecl->Name;
    IsExtensionClass = classDecl->IsExtensionClass;

    if (IsExtensionClass) {
        _baseClassName = classDecl->BaseClass;
    }

    // 
    for (AST::MethodDeclNode* methodDecl: ClassDecl->Methods) {
        ASTMethod* method = new ASTMethod(methodDecl);
        Methods.insert({method->Name, method});
    }
    for (AST::VarDeclNode* variableDecl: ClassDecl->Variables) {
        ASTVariable* variable = new ASTVariable(variableDecl);
        Variables.insert({variable->Name, variable});
    }
}

ASTMethod* ASTClass::GetMethod(std::string methodName) {
    // search for the method definition in our local list
    auto lookupResult = Methods.find(methodName);
    if (lookupResult != Methods.end()) {
        return lookupResult->second;
    }
    // if we didn't find it in our local list, check our base class iff we're an extension class
    if (IsExtensionClass) {
        return BaseClass->GetMethod(methodName);
    }
    return nullptr;
}
ASTVariable* ASTClass::GetVariable(std::string variableName) {
    // search for the variable in our local list
    auto lookupResult = Variables.find(variableName);
    if (lookupResult != Variables.end()) {
        return lookupResult->second;
    }
    // if we didn't find it locally, check our base class iff we're an extension class
    if (IsExtensionClass) {
        return BaseClass->GetVariable(variableName);
    }
    return nullptr;
}

ASTClass* ASTClassTable::GetClass(std::string className) {
    auto lookupResult = Classes.find(className);
    return lookupResult != Classes.end() ?
                lookupResult->second :
                nullptr;
}

bool ASTClassTable::Contains(std::string className) {
    return Classes.find(className) != Classes.end();
}

void ASTClassTable::AddClass(AST::ClassDeclNode* classDecl) {
    ASTClass* classObject = new ASTClass(classDecl);
    Classes.insert({classObject->Name, classObject});
}

void ASTClassTable::Finalize() {
    // iterate through the loaded classes and resolve inheritance
    for (auto const& [className, classObject] : Classes) {
        if (classObject->IsExtensionClass) {
            classObject->BaseClass = GetClass(classObject->_baseClassName);
        }
    }
}

}} // end namespace