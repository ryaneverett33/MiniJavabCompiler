#pragma once
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class NestedExpNode : public ExpNode {
    public:
        NestedExpNode(ExpNode* expression)
            : ExpNode(ExpKind::Nested),
            Expression(expression) {}
        void Str(std::ostream& out) override {
            out << "(";
            Expression->Str(out);
            out << ")";
        }

        ExpNode* Expression;
};

}}} // end namespace 