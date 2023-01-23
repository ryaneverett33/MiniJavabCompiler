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
        void Dbg() {}

        std::string Name;
};

class NewArrayObjectNode : public ObjectNode {
    public:
        NewArrayObjectNode(TypeNode* type, IndexNode* index)
            : ObjectNode(),
            Type(type),
            Index(index) {}
        void Dbg() {}

        TypeNode* Type;
        IndexNode* Index;
};

}} // end namespace 