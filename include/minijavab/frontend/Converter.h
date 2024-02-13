#pragma once
#include "minijavab/frontend/frontend.h"

namespace MiniJavab {
namespace Core {
namespace IR {
    class Module;
}} // end Core/IR namespace

namespace Frontend {
namespace AST {
    class ProgramNode;
} // end AST namespace

class ASTConverter {
    public:
        static Core::IR::Module* Convert(AST::ProgramNode* program, ASTClassTable* table, std::string fileName);
    protected:
        void createClassMetadata();
        void createMetadataTypes();
    private:
        ASTConverter(ASTClassTable* table, std::string fileName);

        ASTClassTable* _classTable;
        Core::IR::Module* _module;
};

}} // end namespace