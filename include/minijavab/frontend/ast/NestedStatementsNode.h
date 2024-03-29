#pragma once
#include <vector>
#include "minijavab/frontend/ast/StatementNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class NestedStatementsNode : public StatementNode {
    public:
        NestedStatementsNode(std::vector<StatementNode*> statements)
        : StatementNode(StatementKind::Nested),
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

}}} // end namespace