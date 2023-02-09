#pragma once
#include "Node.h"

namespace MiniJavab {
namespace AST {

enum class OperatorType {
    Add,
    Subtract,
    Multiply,
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
        std::string OperatorStr(OperatorType op) {
            switch (op) {
                case OperatorType::Add:
                    return "+";
                case OperatorType::Subtract:
                    return "-";
                case OperatorType::Multiply:
                    return "*";
                case OperatorType::Divide:
                    return "/";
                case OperatorType::Factorial:
                    return "!";
                case OperatorType::BooleanAnd:
                    return "&&";
                case OperatorType::BooleanOr:
                    return "||";
                case OperatorType::LessThan:
                    return "<";
                case OperatorType::GreaterThan:
                    return ">";
                case OperatorType::LessThanEqualTo:
                    return "<=";
                case OperatorType::GreaterThanEqualTo:
                    return ">=";
                case OperatorType::EqualTo:
                    return "==";
                case OperatorType::NotEqualTo:
                    return "!=";
            }
        }
};

}}