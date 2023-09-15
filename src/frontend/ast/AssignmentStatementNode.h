#pragma once
#include "StatementNode.h"
#include "ExpNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class AssignmentStatementNode : public StatementNode {
    public:
        AssignmentStatementNode(std::string name, ExpNode* expression)
        : StatementNode(StatementKind::Assignment),
        Name(name),
        Expression(expression) {}
        void Str(std::ostream& out) override {
            out << Name << " = ";
            Expression->Str(out);
            out << ";";
        }
        virtual bool IsIndexedAssignment() const { return false; }

        std::string Name;
        ExpNode* Expression;
};
class AssignmentIndexStatementNode : public AssignmentStatementNode {
    public:
        AssignmentIndexStatementNode(std::string name, IndexNode* index, ExpNode* expression)
        : AssignmentStatementNode(name, expression),
        Index(index) {}
        void Str(std::ostream& out) override {
            out << Name;
            Index->Str(out);
            out << " = ";
            Expression->Str(out);
            out << ";";
        }
        bool IsIndexedAssignment() const override { return true; }

        IndexNode* Index;
};

}}} // end namespace