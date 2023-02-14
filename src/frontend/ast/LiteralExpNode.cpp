#include <iostream>

#include "LiteralExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

IntegerLiteralExpNode::IntegerLiteralExpNode(int literal)
    : ExpNode(),
    Value(literal) { }

void IntegerLiteralExpNode::Str(std::ostream& out) {
    out << std::to_string(Value);
}

BooleanLiteralExpNode::BooleanLiteralExpNode(bool literal)
    : ExpNode(),
    Value(literal) { }
void BooleanLiteralExpNode::Str(std::ostream& out) {
    out << std::boolalpha << Value;
}

StringLiteralExpNode::StringLiteralExpNode(std::string literal)
    : ExpNode(),
    Value(literal) { }

void StringLiteralExpNode::Str(std::ostream& out) {
    out << Value;
}

}}} // end namespace