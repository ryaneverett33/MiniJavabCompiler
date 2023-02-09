#pragma once
#include <vector>
#include "StatementNode.h"

namespace MiniJavab {
namespace AST {

class NestedStatementsNode : public StatementNode {
    public:
        NestedStatementsNode(std::vector<StatementNode*> statements)
        : StatementNode(),
        Statements(statements) {}
        void Str(std::ostream& out) override {
            for (int statementIndex = 0; statementIndex < Statements.size(); statementIndex++) {
                StatementNode* statement = Statements[statementIndex];
                statement->Str(out);
                if ((statementIndex + 1) < Statements.size()) { out << std::endl; }
            }
        }

        std::vector<StatementNode*> Statements;
};

}} // end namespace