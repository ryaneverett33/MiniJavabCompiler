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
        void Dbg() {};

        std::vector<StatementNode*> Statements;
};

}} // end namespace