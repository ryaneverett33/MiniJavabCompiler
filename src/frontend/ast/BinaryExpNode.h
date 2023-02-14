#pragma once
#include "ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class BinaryExpNode : public ExpNode {
    public:
        BinaryExpNode(OperatorType op, ExpNode* left, ExpNode* right);
        void Str(std::ostream& out) override;
        
        OperatorType Operator;
        ExpNode* LeftSide;
        ExpNode* RightSide;
};

}}} // end namespace