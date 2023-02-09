#pragma once
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class WhileStatementNode : public StatementNode {
    public:
        WhileStatementNode(ExpNode* expression, StatementNode* statement)
        : StatementNode(),
        Expression(expression),
        Statement(statement) {}
        void Str(std::ostream& out) override {
            out << "while(";
            Expression->Str(out);
            out << ") {" << std::endl;
            Statement->Str(out);
            out << std::endl << "}";
        }

        ExpNode* Expression;
        StatementNode* Statement;
};

}} // end namespace