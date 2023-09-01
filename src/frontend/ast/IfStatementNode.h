#pragma once
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class IfStatementNode : public StatementNode {
    public:
        IfStatementNode(ExpNode* expression, StatementNode* ifStatement, StatementNode* elseStatement)
        : StatementNode(StatementKind::If),
        Expression(expression),
        IfStatement(ifStatement),
        ElseStatement(elseStatement) {}
        void Str(std::ostream& out) override;

        ExpNode* Expression;
        StatementNode* IfStatement;
        StatementNode* ElseStatement;
};

}}} // end namespace