#pragma once
#include "minijavab/frontend/frontend.h"

#include <unordered_map>

namespace MiniJavab {
namespace Core {
namespace IR {
    class Module;
    class Type;
    class GlobalVariable;
    class StructType;
}} // end Core/IR namespace

namespace Frontend {
namespace AST {
    class ProgramNode;
    class Type;
} // end AST namespace

/// Handles converting/lifting the MiniJavab AST to an IR form
class ASTConverter {
    public:
        /// Convert the AST representation of a program to its IR form
        /// @param program The Program AST to convert
        /// @param table The resolved class/methods/variables definition table
        /// @param fileName The original filename the AST was generated from (used for module naming)
        /// @return The IR form if successfully converted, nullptr otherwise
        static Core::IR::Module* Convert(AST::ProgramNode* program, ASTClassTable* table, std::string fileName);
    protected:
        /// Creates the metadata global variables for the AST
        void CreateClassMetadata();
        /// Creates metadata types used during the metadata construction phase
        void CreateMetadataTypes();
        /// Create types for each class in the AST
        void CreateClassTypes();
        /// Creates the metadata variable for a method
        /// @note Types are added to @a _classTypeTable
        /// @param parentClass The class containing the method
        /// @param method The method to create a type for
        /// @return The newly created global variable that's been added to the module
        Core::IR::GlobalVariable* CreateMetadataMethod(ASTClass* parentClass, ASTMethod* method);
        /// Resolve an AST Type to an IR-equivalent type
        /// @param type The AST Type to resolve
        /// @return The new IR type
        Core::IR::Type* ResolveASTType(Frontend::AST::Type* type);
    private:
        ASTConverter(ASTClassTable* table, std::string fileName);

        /// The class table with all of the classes, methods, and variables
        ASTClassTable* _classTable;

        /// The new module this converter is populating
        Core::IR::Module* _module;

        /// A table of all of the class names and their type definition
        std::unordered_map<std::string, Core::IR::StructType*> _classTypeTable;
};

}} // end namespace