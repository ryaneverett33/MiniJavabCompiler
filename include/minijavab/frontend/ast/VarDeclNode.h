#pragma once
#include <string>
#include "minijavab/frontend/ast/TypeNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTVariable;

namespace AST {

class VarDeclNode : public Node {
    public:
        VarDeclNode(TypeNode* type, std::string name);
        VarDeclNode(std::string type, std::string name);
        void Str(std::ostream& out) override;

        TypeNode* Type;
        std::string Name;

        /// A reference to the variable in the symbol table
        ASTVariable* VariableInfo = nullptr;
};

}}} // end namespace