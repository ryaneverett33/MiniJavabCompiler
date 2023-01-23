#pragma once
#include <string>
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class IntegerLiteralExpNode : public ExpNode {
    public:
        IntegerLiteralExpNode(int literal);
        void Dbg() override;

        int Value;
};
class BooleanLiteralExpNode : public ExpNode {
    public:
        BooleanLiteralExpNode(bool literal);
        void Dbg() override;

        bool Value;
};
class StringLiteralExpNode : public ExpNode {
    public:
        StringLiteralExpNode(std::string literal);
        void Dbg() override;

        std::string Value;
};
/*class ObjectLiteralExpNode : public ExpNode {
    public:
        ObjectLiteralExpNode(object literal);
    private:
        // object value
};*/

}}