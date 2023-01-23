#include "UnaryExpNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

UnaryExpNode::UnaryExpNode(OperatorType op, ExpNode* exp)
    : ExpNode(),
    Operator(op),
    Expression(exp) { }

}} // namespace