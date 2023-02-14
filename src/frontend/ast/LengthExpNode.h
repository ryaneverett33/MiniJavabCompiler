#pragma once
#include <string>
#include "ExpNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace Frontend {
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
        void Str(std::ostream& out) override {
            out << Name;
            if (Index != nullptr) {
                Index->Str(out);
            }
            out << ".length";
        }

        std::string Name;
        IndexNode* Index;
};

}}} // end namespace 