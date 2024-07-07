#include "minijavab/frontend/ASTClassTable.h"
#include "minijavab/frontend/frontend.h"

namespace MiniJavab {
namespace Frontend {

ASTVariable::ASTVariable(AST::VarDeclNode* declaration, ASTMethod* parentMethod)
    : VarDecl(declaration),
    ParentMethod(parentMethod),
    ClassVariable(false)
{
    Name = declaration->Name;
    Type = declaration->Type->ResolveType();
}

ASTVariable::ASTVariable(AST::VarDeclNode* declaration, ASTClass* parentClass)
    : VarDecl(declaration),
    ParentClass(parentClass),
    ClassVariable(true)
{
    Name = declaration->Name;
    Type = declaration->Type->ResolveType();
}

ASTVariable::ASTVariable(std::string name, ASTClass* parentClass)
    : VarDecl(nullptr),
    ParentClass(parentClass),
    ClassVariable(true)
{
    Name = name;
    Type = parentClass->Type;
}

bool ASTVariable::IsObjectType() const {
    return VarDecl->Type->IsObjectType();
}

ASTMethod::ASTMethod(AST::MethodDeclNode* methodDecl, ASTClass* parentClass)
    : MethodDecl(methodDecl),
    ParentClass(parentClass)
{
    Name = methodDecl->Name;
    ReturnType = methodDecl->Type->ResolveType();

    // load variable info by examining the MethodDeclNode's variable list
    for (AST::VarDeclNode* variableDecl: methodDecl->Variables) {
        ASTVariable* variable = new ASTVariable(variableDecl, this);
        if (Variables.find(variable->Name) != Variables.end()) {
            throw std::invalid_argument("Variable already defined");
        }

        Variables.insert({variable->Name, variable});
    }

    // load parameter info from the node's method list
    for (AST::VarDeclNode* parameterDecl: methodDecl->Parameters) {
        ASTVariable* parameter = new ASTVariable(parameterDecl, this);
        if (Parameters.find(parameter->Name) != Parameters.end()) {
            throw std::invalid_argument("Parameter already defined");
        }

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
    Name(classDecl->Name),
    IsExtensionClass(classDecl->IsExtensionClass),
    Type(new AST::ObjectType(Name))
{
    if (IsExtensionClass) {
        _baseClassName = classDecl->BaseClass;
    }

    for (AST::MethodDeclNode* methodDecl: ClassDecl->Methods) {
        ASTMethod* method = new ASTMethod(methodDecl, this);
        if (Methods.find(method->Name) != Methods.end()) {
            throw std::invalid_argument("Method already defined");
        }

        Methods.insert({method->Name, method});
    }
    for (AST::VarDeclNode* variableDecl: ClassDecl->Variables) {
        ASTVariable* variable = new ASTVariable(variableDecl, this);
        if (Variables.find(variable->Name) != Variables.end()) {
            throw std::invalid_argument("Class variable already defined");
        }

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

bool ASTClassTable::AddClass(AST::ClassDeclNode* classDecl) {
    ASTClass* classObject = nullptr;
    try {
        classObject = new ASTClass(classDecl);
    }
    catch (std::invalid_argument& arg) {
        return false;
    }
    
    if (Classes.find(classObject->Name) != Classes.end()) {
        return false;
    }
    Classes.insert({classObject->Name, classObject});

    classObject->Variables.insert({"this", new ASTVariable("this", classObject)});
    return true;
}

bool ASTClassTable::Finalize(std::ostream& errs) {
    bool foundErrors = false;

    // iterate through the loaded classes and resolve inheritance
    for (auto const& [className, classObject] : Classes) {
        if (classObject->IsExtensionClass) {
            classObject->BaseClass = GetClass(classObject->_baseClassName);
            if (classObject->BaseClass == nullptr) {
                foundErrors = true;
                errs << "cannot find symbol: class '" + classObject->_baseClassName + "'" << "\n";
            }
        }
    }

    // iterate through all variables and resolve class information
    for (auto const& [className, classObject] : Classes) {
        for (auto const& [variableName, variableObject] : classObject->Variables) {
            if (variableObject->Type->IsObjectType()) {
                AST::ObjectType* objectType = static_cast<AST::ObjectType*>(variableObject->Type);
                variableObject->ClassInfo = GetClass(objectType->TypeName);
                if (variableObject->ClassInfo == nullptr) {
                    foundErrors = true;
                    errs << "cannot find symbol: class '" + objectType->TypeName + "'" << "\n";
                }
            }
        }
        for (auto const& [methodName, methodObject] : classObject->Methods) {
            for (auto const& [variableName, variableObject] : methodObject->Variables) {
                if (variableObject->Type->IsObjectType()) {
                    AST::ObjectType* objectType = static_cast<AST::ObjectType*>(variableObject->Type);
                    variableObject->ClassInfo = GetClass(objectType->TypeName);
                    if (variableObject->ClassInfo == nullptr) {
                        foundErrors = true;
                        errs << "cannot find symbol: class '" + objectType->TypeName + "'" << "\n";
                    }
                }
            }
        }
    }
    return !foundErrors;
}

}} // end namespace