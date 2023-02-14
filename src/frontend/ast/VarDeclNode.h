#pragma once
#include <string>
#include "TypeNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class VarDeclNode : public Node {
    public:
        VarDeclNode(TypeNode* type, std::string name);
        VarDeclNode(std::string type, std::string name);
        void Str(std::ostream& out) override;

        TypeNode* Type;
        std::string Name;
};

}}} // end namespace