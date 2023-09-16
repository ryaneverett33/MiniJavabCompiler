#pragma once
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class UnaryExpNode : public ExpNode {
    public:
        UnaryExpNode(OperatorType op, ExpNode* exp);
        void Str(std::ostream& out) override {
            out << OperatorStr(Operator);
            Expression->Str(out);
        }
  
        OperatorType Operator;
        ExpNode* Expression;
};

}}} // end namespace