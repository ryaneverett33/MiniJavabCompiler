#pragma once
#include "Node.h"

namespace MiniJavab {
namespace AST {

class ObjectNode : public Node {
    public:
        ObjectNode()
            : Node() {}
        void Dbg() {}
};

class NamedObjectNode : public ObjectNode {
    public:
        NamedObjectNode(std::string name)
            : ObjectNode(),
            Name(name) {}
        void Dbg() {}

        std::string Name;
};

class ThisObjectNode : public ObjectNode {
    public:
        ThisObjectNode() : ObjectNode() {}
        void Dbg() {}
};

}} // end namespace 