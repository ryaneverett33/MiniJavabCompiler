#pragma once
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class ReturnStatementNode : public StatementNode {
    public:
        ReturnStatementNode(ExpNode* expression)
        : StatementNode(),
        Expression(expression) {}
        void Str(std::ostream& out) override {
            out << "return ";
            Expression->Str(out);
            out << ";";
        }

        ExpNode* Expression;
};

}} // end namespace