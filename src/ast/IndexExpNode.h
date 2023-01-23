#pragma once
#include "ExpNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace AST {

class IndexExpNode : public ExpNode {
    public:
        IndexExpNode(IndexNode* index)
            : ExpNode(),
            Index(index) {}
        void Dbg() {}

        IndexNode* Index;
};

}} // end namespace 