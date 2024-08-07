#pragma once
#include <string>
#include "minijavab/frontend/ast/ExpNode.h"
#include "minijavab/frontend/ast/IndexNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTVariable;

namespace AST {

class LengthExpNode : public ExpNode {
    // hello.length, Name: "hello"
    public:
        LengthExpNode(std::string name)
            : ExpNode(ExpKind::LengthMethod),
            Name(name),
            Index(nullptr) {}

        LengthExpNode(std::string name, IndexNode* index)
            : ExpNode(ExpKind::LengthMethod),
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

        /// The object being referenced
        ASTVariable* ObjectInfo = nullptr;
};

}}} // end namespace 