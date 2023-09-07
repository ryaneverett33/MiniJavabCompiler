#pragma once
#include <string>
#include "ObjectNode.h"
#include "TypeNode.h"
#include "IndexNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class NewObjectNode : public NamedObjectNode {
    public:
        NewObjectNode(std::string name)
            : NamedObjectNode(name) {}
        void Str(std::ostream& out) override {
            out << "new " << Name << "()";
        }
        virtual bool IsNewObject() override { return true; }
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
        bool IsNewArray() override { return true; }

        TypeNode* Type;
        IndexNode* Index;
};

}}} // end namespace 