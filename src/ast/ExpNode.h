#pragma once
#include "Node.h"

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
        ExpNode()
        : Node() {}
        virtual void Dbg() {}
};

}}