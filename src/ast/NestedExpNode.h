#pragma once
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class NestedExpNode : public ExpNode {
    public:
        NestedExpNode(ExpNode* expression)
            : ExpNode(),
            Expression(expression) {}
        void Dbg() {}

        ExpNode* Expression;
};

}} // end namespace 