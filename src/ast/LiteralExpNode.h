#pragma once
#include <string>
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class IntegerLiteralExpNode : public ExpNode {
    public:
        IntegerLiteralExpNode(int literal);
        void Str(std::ostream& out) override;

        int Value;
};
class BooleanLiteralExpNode : public ExpNode {
    public:
        BooleanLiteralExpNode(bool literal);
        void Str(std::ostream& out) override;

        bool Value;
};
class StringLiteralExpNode : public ExpNode {
    public:
        StringLiteralExpNode(std::string literal);
        void Str(std::ostream& out) override;

        std::string Value;
};

}}