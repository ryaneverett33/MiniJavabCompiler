#pragma once
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class UnaryExpNode : public ExpNode {
    public:
        UnaryExpNode(OperatorType op, ExpNode* exp);
        void Dbg() override {}
  
        OperatorType Operator;
        ExpNode* Expression;
};

}}