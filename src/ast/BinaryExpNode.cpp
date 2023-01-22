#include "UnaryExpNode.h"
#include "BinaryExpNode.h"

namespace MiniJavab {
namespace AST {

BinaryExpNode::BinaryExpNode(OperatorType op, ExpNode* left, ExpNode* right)
    : ExpNode({left, right}) {
        this->op = op;
}

}}