#pragma once
#include "Node.h"

namespace MiniJavab {
namespace Frontend {
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

enum class ExpKind {
    Binary,
    Unary,
    Literal,
    LengthMethod,
    MethodCall,
    Nested,
    Object,
    Index
};

class ExpNode : public Node {
    public:
        ExpNode(ExpKind kind)
            : Node(),
            Kind(kind) 
        {}
        
        /// Converts an OperatorType to the MiniJavab equivalent
        /// @param op Operator to convert
        /// @return String representation of the operator
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

        bool IsBinaryExpression() { return Kind == ExpKind::Binary; }
        bool IsUnaryExpression() { return Kind == ExpKind::Unary; }
        bool IsLiteralExpression() { return Kind == ExpKind::Literal; }
        bool IsLengthMethodExpression() { return Kind == ExpKind::LengthMethod; }
        bool IsMethodCallExpression() { return Kind == ExpKind::MethodCall; }
        bool IsNestedExpression() { return Kind == ExpKind::Nested; }
        bool IsObjectExpression() { return Kind == ExpKind::Object; }
        bool IsIndexExpression() { return Kind == ExpKind::Index; }

        /// The Kind of Expression this is
        ExpKind Kind;
};

}}}