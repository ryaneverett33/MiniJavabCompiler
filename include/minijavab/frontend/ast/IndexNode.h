#pragma once
#include <string>
#include <vector>
#include "minijavab/frontend/ast/Node.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class IndexNode : public Node
{
    public:
        IndexNode(ExpNode *expression)
            : Node(),
            Expressions({expression}) {}
        void Str(std::ostream &out) override {
            for (ExpNode* expression : Expressions) {
                out << "[";
                expression->Str(out);
                out << "]";
            }
        }

        std::vector<ExpNode *> Expressions;
};

}}} // end namespace