#include "UnaryExpNode.h"
#include "BinaryExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

BinaryExpNode::BinaryExpNode(OperatorType op, ExpNode* left, ExpNode* right)
    : ExpNode(),
    Operator(op),
    LeftSide(left),
    RightSide(right)
    {}

void BinaryExpNode::Str(std::ostream& out) {
    LeftSide->Str(out);
    out << " " << OperatorStr(Operator) << " ";
    RightSide->Str(out);
}

}}} // end namespace