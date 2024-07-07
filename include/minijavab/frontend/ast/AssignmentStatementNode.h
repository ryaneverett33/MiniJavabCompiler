#pragma once
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/ExpNode.h"
#include "minijavab/frontend/ast/IndexNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTVariable;

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

        /// The variable we're assigning the result of expression to
        ASTVariable* AssignedVariable = nullptr;
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