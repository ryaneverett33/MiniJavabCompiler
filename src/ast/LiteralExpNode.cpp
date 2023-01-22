#include <iostream>

#include "LiteralExpNode.h"

namespace MiniJavab {
namespace AST {

IntegerLiteralExpNode::IntegerLiteralExpNode(int literal)
    : ExpNode({}),
    value(literal) { }

void IntegerLiteralExpNode::Dbg() {
    std::cout << "Integer Literal: " << std::to_string(value) << std::endl;
}

BooleanLiteralExpNode::BooleanLiteralExpNode(bool literal)
    : ExpNode({}),
    value(literal) { }
void BooleanLiteralExpNode::Dbg() {
    std::cout << "Boolean Literal: " << std::boolalpha << value << std::endl;
}

StringLiteralExpNode::StringLiteralExpNode(std::string literal)
    : ExpNode({}),
    value(literal) { }

void StringLiteralExpNode::Dbg() {
    std::cout << "String Literal: " << value << std::endl;
}

}} // end namespace