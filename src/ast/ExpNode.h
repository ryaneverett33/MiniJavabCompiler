#pragma once
#include "Node.h"
#include <initializer_list>

namespace MiniJavab {
namespace AST {

enum OperatorType {
    Add,
    Subtract,
    Multiple,
    Divide,
    Factorial,
    BooleanAnd,
    BooleanOr,
    LessThan,
    GreaterThan,
    LessThanEqualTo,
    GreaterThanEqualTo,
    EqualTo,
    NotEqualTo
};

class ExpNode : public Node {
    public:
        ExpNode(std::initializer_list<Node*> children)
        : Node(children) {}
        void Dbg() {}
};

}}