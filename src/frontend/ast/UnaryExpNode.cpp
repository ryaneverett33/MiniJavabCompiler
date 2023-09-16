#include "minijavab/frontend/ast/UnaryExpNode.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

UnaryExpNode::UnaryExpNode(OperatorType op, ExpNode* exp)
    : ExpNode(ExpKind::Unary),
    Operator(op),
    Expression(exp) { }

}}} // namespace