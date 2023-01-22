#include "UnaryExpNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

UnaryExpNode::UnaryExpNode(OperatorType op, ExpNode* child)
    : ExpNode({child}) {
        this->op = op;
}

}} // namespace