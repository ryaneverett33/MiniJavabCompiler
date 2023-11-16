#pragma once
#include <string>
#include <vector>
#include "minijavab/frontend/ast/Node.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

enum class StatementKind {
    Assignment,
    If,
    Nested,
    Print,
    Return,
    While
};

class StatementNode : public Node {
    public:
        StatementNode(StatementKind kind)
            : Node(),
            Kind(kind)
        {}

        bool IsAssignmentStatement() { return Kind == StatementKind::Assignment; }
        bool IsIfStatement() { return Kind == StatementKind::If; }
        bool IsNestedStatement() { return Kind == StatementKind::Nested; }
        bool IsPrintStatement() { return Kind == StatementKind::Print; }
        bool IsReturnStatement() { return Kind == StatementKind::Return; }
        bool IsWhileStatement() { return Kind == StatementKind::While; }

        StatementKind Kind;
};

}}} // end namespace