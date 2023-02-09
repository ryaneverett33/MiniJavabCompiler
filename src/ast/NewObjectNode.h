#pragma once
#include <string>
#include "ObjectNode.h"
#include "TypeNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace AST {

class NewObjectNode : public ObjectNode {
    public:
        NewObjectNode(std::string name)
            : ObjectNode(),
            Name(name) {}
        void Str(std::ostream& out) override {
            out << "new " << Name << "()";
        }

        std::string Name;
};

class NewArrayObjectNode : public ObjectNode {
    public:
        NewArrayObjectNode(TypeNode* type, IndexNode* index)
            : ObjectNode(),
            Type(type),
            Index(index) {}
        void Str(std::ostream& out) override {
            out << "new ";
            Type->Str(out);
            Index->Str(out);
        }

        TypeNode* Type;
        IndexNode* Index;
};

}} // end namespace 