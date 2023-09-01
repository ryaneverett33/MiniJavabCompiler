#include "UnaryExpNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

UnaryExpNode::UnaryExpNode(OperatorType op, ExpNode* exp)
    : ExpNode(ExpKind::Unary),
    Operator(op),
    Expression(exp) { }

}}} // namespace