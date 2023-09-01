#pragma once
#include <string>
#include "ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

enum class LiteralExpKind {
    Integer,
    Boolean,
    String
};

class LiteralExpNode : public ExpNode {
    public:
        LiteralExpNode(LiteralExpKind kind)
            : ExpNode(ExpKind::Literal),
            LiteralKind(kind) {}

        bool IsIntegerLiteral() { return LiteralKind == LiteralExpKind::Integer; }
        bool IsBooleanLiteral() { return LiteralKind == LiteralExpKind::Boolean; }
        bool IsStringLiteral() { return LiteralKind == LiteralExpKind::String; }

        LiteralExpKind LiteralKind;
};

class IntegerLiteralExpNode : public LiteralExpNode {
    public:
        IntegerLiteralExpNode(int literal);
        void Str(std::ostream& out) override;

        int Value;
};
class BooleanLiteralExpNode : public LiteralExpNode {
    public:
        BooleanLiteralExpNode(bool literal);
        void Str(std::ostream& out) override;

        bool Value;
};
class StringLiteralExpNode : public LiteralExpNode {
    public:
        StringLiteralExpNode(std::string literal);
        void Str(std::ostream& out) override;

        std::string Value;
};

}}} // end namespace