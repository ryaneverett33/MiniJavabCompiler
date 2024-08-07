#pragma once
#include <string>
#include <unordered_map>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/ast/Type.h"

namespace MiniJavab {
namespace Frontend {

class ASTClassTable;
class ASTVariable;
class ASTMethod;
class ASTClass;

class ASTVariable {
    public:
        ASTVariable(AST::VarDeclNode* declaration, ASTMethod* parentMethod);
        ASTVariable(AST::VarDeclNode* declaration, ASTClass* parentClass);
        ASTVariable(std::string name, ASTClass* parentClass);

        /// Whether or not this variable is an object type or a primitive type
        /// @return True if it's an object type and has class information, false otherwise
        bool IsObjectType() const;

        // Name of the variable
        std::string Name;

        // The Type of this variable
        AST::Type* Type;

        // The AST node of the variable declaration, null if it's a `this` variable
        AST::VarDeclNode* VarDecl;

        /// The method that contains this variable definition, nullptr if it's a class variable
        ASTMethod* ParentMethod = nullptr;

        /// The class that contains this variable definition, nullptr if it's not a class variable
        ASTClass* ParentClass = nullptr;

        /// Class information about this variable if it's an object type
        ASTClass* ClassInfo = nullptr;

        /// Whether or not this variable is defined by a class
        bool ClassVariable;
};

class ASTMethod {
    public:
        ASTMethod(AST::MethodDeclNode* methodDecl, ASTClass* parentClass);

        /// Lookup a local method variable by it's name. Local method variables are scoped to the method
        /// and are not valid in a class context.
        /// @param variableName the name of the variable to lookup
        /// @return The variable definition if it exists, else `nullptr`
        ASTVariable* GetVariable(std::string variableName);

        /// Lookup a method parameter by it's name. Method parameters are identical to variables but are
        /// "defined" in the method signature.
        /// @param parameterName the name of the parameter to lookup
        /// @return The parameter definition if it exists, else `nullptr`
        ASTVariable* GetParameter(std::string parameterName);

        // The name of the method
        std::string Name;

        // The type of value this method returns
        AST::Type* ReturnType;

        // The AST Node of the method declaration
        AST::MethodDeclNode* MethodDecl;

        /// The class containing this method
        ASTClass* ParentClass;

        // All defined variables in the method stored by Name
        std::unordered_map<std::string, ASTVariable*> Variables;

        // All parameters given to the method stored by Name
        std::unordered_map<std::string, ASTVariable*> Parameters;
};

class ASTClass {
    public:
        ASTClass(AST::ClassDeclNode* classDecl);

        /// Lookup a method by it's name. If this class is an extension class
        /// then the BaseClass will be searched too. Method resolution is recursive
        /// for chained inheritance.
        /// @param methodName The method to lookup
        /// @return The method definition if it exists, else nullptr
        ASTMethod* GetMethod(std::string methodName);

        /// Lookup a variable by it's name. Similar to method resolution, the search
        /// is recursive if the class uses inheritance
        /// @param variableName The variable to lookup
        /// @return The variable definition if it exists, else nullptr
        /// @see ASTClass::GetMethod
        ASTVariable* GetVariable(std::string variableName);

        // The name of the class
        std::string Name;

        // Whether or not the class extends a base class
        bool IsExtensionClass = false;

        // Reference to the base class if this is an extension class, else nullptr
        ASTClass* BaseClass = nullptr;

        // The AST Node of the class declaration
        AST::ClassDeclNode* ClassDecl;

        // The Type of this class
        AST::Type* Type;

        // All defined methods in the class stored by Name
        std::unordered_map<std::string, ASTMethod*> Methods;

        // All defined variables in the class stored by Name
        std::unordered_map<std::string, ASTVariable*> Variables;
    private:
        std::string _baseClassName;

        friend class ASTClassTable;
};

class ASTClassTable {
    public:
        ASTClassTable() {};

        /// Lookup a class by it's name.
        /// @param className Name of the class to lookup
        /// @return The class definition if it exists, else nullptr
        ASTClass* GetClass(std::string className);

        /// Lookup if the class has been loaded into the table.
        /// Loaded classes can then be retrieved with `ASTClassTable::GetClass()`
        /// @param className Name of the class to lookup
        /// @return True if a class exists by the given name, False otherwise
        bool Contains(std::string className);

        /// Parses and adds a class to the table
        /// @param classDecl The class definition to add
        /// @return True if the class was successfully added, false otherwise
        bool AddClass(AST::ClassDeclNode* classDecl);

        /// Resolves inheritance after all classes have been loaded.
        /// Should be called to finish table construction.

        /// Perform any additional class table finalization, such as resolving inheritance and
        /// object class information. Initial error checking is done at this point too
        /// @return True if finalization was successful and no errors were found, false if 
        /// errors were found
        bool Finalize(std::ostream& errs);

        // All defined classes in the table stored by Name
        std::unordered_map<std::string, ASTClass*> Classes;
};

}} // end namespace