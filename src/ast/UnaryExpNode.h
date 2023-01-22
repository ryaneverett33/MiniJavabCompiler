#pragma once
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class UnaryExpNode : public ExpNode {
    public:
        UnaryExpNode(OperatorType op, ExpNode* child);
        void Dbg() override {}
    private:
        OperatorType op;
};

}}