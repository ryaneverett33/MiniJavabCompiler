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
        void Dbg() {};

        ExpNode* Expression;
        StatementNode* Statement;
};

}} // end namespace