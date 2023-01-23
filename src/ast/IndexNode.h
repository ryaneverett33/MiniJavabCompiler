#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class IndexNode : public Node {
    public:
        IndexNode(ExpNode* expression)
                : Node(),
                Expressions({expression}) { }
        void Dbg() {}

        std::vector<ExpNode*> Expressions;
};

}} // end namespace