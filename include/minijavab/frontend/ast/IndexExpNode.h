#pragma once
#include "minijavab/frontend/ast/ExpNode.h"
#include "minijavab/frontend/ast/IndexNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTVariable;

namespace AST {

class IndexExpNode : public ExpNode {
    public:
        IndexExpNode(std::string object, IndexNode* index)
            : ExpNode(ExpKind::Index),
            Object(object),
            Index(index) {}
        void Str(std::ostream& out) override {
            out << Object;
            Index->Str(out);
        }

        std::string Object;
        IndexNode* Index;

        /// The object being stored to or retrieved from
        ASTVariable* ObjectInfo = nullptr;
};

}}} // end namespace 