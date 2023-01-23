#pragma once
#include "StatementNode.h"
#include "ExpNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace AST {

class AssignmentStatementNode : public StatementNode {
    public:
        AssignmentStatementNode(std::string name, ExpNode* expression)
        : StatementNode(),
        Name(name),
        Expression(expression) {}
        void Dbg() {};

        std::string Name;
        ExpNode* Expression;
};
class AssignmentIndexStatementNode : public AssignmentStatementNode {
    public:
        AssignmentIndexStatementNode(std::string name, IndexNode* index, ExpNode* expression)
        : AssignmentStatementNode(name, expression),
        Index(index) {}
        void Dbg() {}

        IndexNode* Index;
};

}} // end namespace