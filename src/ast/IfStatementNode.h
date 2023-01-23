#pragma once
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class IfStatementNode : public StatementNode {
    public:
        IfStatementNode(ExpNode* expression, StatementNode* ifStatement, StatementNode* elseStatement)
        : StatementNode(),
        Expression(expression),
        IfStatement(ifStatement),
        ElseStatement(elseStatement) {}
        void Dbg() {};

        ExpNode* Expression;
        StatementNode* IfStatement;
        StatementNode* ElseStatement;
};

}} // end namespace