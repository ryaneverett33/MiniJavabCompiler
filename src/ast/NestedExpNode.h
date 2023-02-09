#pragma once
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class NestedExpNode : public ExpNode {
    public:
        NestedExpNode(ExpNode* expression)
            : ExpNode(),
            Expression(expression) {}
        void Str(std::ostream& out) override {
            out << "(";
            Expression->Str(out);
            out << ")";
        }

        ExpNode* Expression;
};

}} // end namespace 