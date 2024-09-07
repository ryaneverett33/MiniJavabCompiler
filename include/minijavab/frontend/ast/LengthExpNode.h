#pragma once
#include <string>
#include "minijavab/frontend/ast/ExpNode.h"
#include "minijavab/frontend/ast/IndexNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTVariable;

namespace AST {

/// Represents getting the length of an array, either single or multi-dimensional.
/// Example: arr.length; arr[0].length
class LengthExpNode : public ExpNode {
    public:
        LengthExpNode(std::string name)
            : ExpNode(ExpKind::LengthMethod),
            Name(name) {}

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
        IndexNode* Index = nullptr;

        /// The object being referenced
        ASTVariable* ObjectInfo = nullptr;
};

}}} // end namespace 