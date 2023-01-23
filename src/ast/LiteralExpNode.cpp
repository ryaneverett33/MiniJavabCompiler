#include <iostream>

#include "LiteralExpNode.h"

namespace MiniJavab {
namespace AST {

IntegerLiteralExpNode::IntegerLiteralExpNode(int literal)
    : ExpNode(),
    Value(literal) { }

void IntegerLiteralExpNode::Dbg() {
    std::cout << "Integer Literal: " << std::to_string(Value) << std::endl;
}

BooleanLiteralExpNode::BooleanLiteralExpNode(bool literal)
    : ExpNode(),
    Value(literal) { }
void BooleanLiteralExpNode::Dbg() {
    std::cout << "Boolean Literal: " << std::boolalpha << Value << std::endl;
}

StringLiteralExpNode::StringLiteralExpNode(std::string literal)
    : ExpNode(),
    Value(literal) { }

void StringLiteralExpNode::Dbg() {
    std::cout << "String Literal: " << Value << std::endl;
}

}} // end namespace