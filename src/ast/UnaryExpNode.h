#pragma once
#include "ExpNode.h"

namespace MiniJavab {
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

}}