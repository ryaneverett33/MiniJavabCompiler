#include "UnaryExpNode.h"
#include "BinaryExpNode.h"

namespace MiniJavab {
namespace AST {

BinaryExpNode::BinaryExpNode(OperatorType op, ExpNode* left, ExpNode* right)
    : ExpNode(),
    Operator(op),
    LeftSide(left),
    RightSide(right)
    {}

}}