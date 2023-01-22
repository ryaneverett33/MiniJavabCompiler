#pragma once
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class BinaryExpNode : public ExpNode {
    public:
        BinaryExpNode(OperatorType op, ExpNode* left, ExpNode* right);
        void Dbg() override {}
    private:
        OperatorType op;
};

}}