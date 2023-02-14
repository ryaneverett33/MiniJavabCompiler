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
        : StatementNode(),
        Name(name),
        Expression(expression) {}
        void Str(std::ostream& out) override {
            CommonStr(out);
            out << ";";
        }

        std::string Name;
        ExpNode* Expression;
    protected:
        void CommonStr(std::ostream& out) {
            out << Name << " = ";
            Expression->Str(out);
        }
};
class AssignmentIndexStatementNode : public AssignmentStatementNode {
    public:
        AssignmentIndexStatementNode(std::string name, IndexNode* index, ExpNode* expression)
        : AssignmentStatementNode(name, expression),
        Index(index) {}
        void Str(std::ostream& out) override {
            CommonStr(out);
            Index->Str(out);
            out << ";";
        }

        IndexNode* Index;
};

}}} // end namespace