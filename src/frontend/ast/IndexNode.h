#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "ExpNode.h"

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