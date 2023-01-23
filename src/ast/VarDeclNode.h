#pragma once
#include <string>
#include "TypeNode.h"

namespace MiniJavab {
namespace AST {

class VarDeclNode : public Node {
    public:
        VarDeclNode(TypeNode* type, std::string name);
        VarDeclNode(std::string type, std::string name);
        void Dbg() {};

        TypeNode* Type;
        std::string Name;
};

}} // end namespace