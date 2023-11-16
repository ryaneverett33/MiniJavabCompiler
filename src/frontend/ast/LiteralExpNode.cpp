#include <iostream>

#include "minijavab/frontend/ast/LiteralExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

IntegerLiteralExpNode::IntegerLiteralExpNode(int literal)
    : LiteralExpNode(LiteralExpKind::Integer),
    Value(literal) { }

void IntegerLiteralExpNode::Str(std::ostream& out) {
    out << std::to_string(Value);
}

BooleanLiteralExpNode::BooleanLiteralExpNode(bool literal)
    : LiteralExpNode(LiteralExpKind::Boolean),
    Value(literal) { }
void BooleanLiteralExpNode::Str(std::ostream& out) {
    out << std::boolalpha << Value;
}

StringLiteralExpNode::StringLiteralExpNode(std::string literal)
    : LiteralExpNode(LiteralExpKind::String),
    Value(literal) { }

void StringLiteralExpNode::Str(std::ostream& out) {
    out << Value;
}

}}} // end namespace