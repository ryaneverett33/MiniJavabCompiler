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
  
        /// The expression operation type
        /// @note Only Add, Subtract, and BooleanNot are valid
        OperatorType Operator;

        /// The expression to perform the operation on
        ExpNode* Expression;
};

}}} // end namespace