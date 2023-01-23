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
        void Dbg() {};

        ExpNode* Expression;
};

}} // end namespace