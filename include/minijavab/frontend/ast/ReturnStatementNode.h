#pragma once
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class ReturnStatementNode : public StatementNode {
    public:
        ReturnStatementNode(ExpNode* expression)
        : StatementNode(StatementKind::Return),
        Expression(expression) {}
        void Str(std::ostream& out) override {
            out << "return ";
            Expression->Str(out);
            out << ";";
        }

        ExpNode* Expression;
};

}}} // end namespace