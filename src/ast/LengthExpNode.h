#pragma once
#include <string>
#include "ExpNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace AST {

class LengthExpNode : public ExpNode {
    public:
        LengthExpNode(std::string name)
            : ExpNode(),
            Name(name),
            Index(nullptr) {}

        LengthExpNode(std::string name, IndexNode* index)
            : ExpNode(),
            Name(name),
            Index(index) {}
        void Dbg() {}

        std::string Name;
        IndexNode* Index;
};

}} // end namespace 