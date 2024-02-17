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

class ASTConverter {
    public:
        static Core::IR::Module* Convert(AST::ProgramNode* program, ASTClassTable* table, std::string fileName);
    protected:
        void CreateClassMetadata();
        void CreateMetadataTypes();
        void CreateClassTypes();
        Core::IR::GlobalVariable* CreateMetadataMethodType(ASTClass* parentClass, ASTMethod* method);
        Core::IR::Type* ResolveASTType(Frontend::AST::Type* type);
    private:
        ASTConverter(ASTClassTable* table, std::string fileName);

        ASTClassTable* _classTable;
        Core::IR::Module* _module;
        std::unordered_map<std::string, Core::IR::StructType*> _classTypeTable;
};

}} // end namespace