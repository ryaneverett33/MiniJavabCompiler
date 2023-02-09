#pragma once
#include "Node.h"

namespace MiniJavab {
namespace AST {

class ObjectNode : public Node {
    public:
        ObjectNode()
            : Node() {}
};

class NamedObjectNode : public ObjectNode {
    public:
        NamedObjectNode(std::string name)
            : ObjectNode(),
            Name(name) {}
        void Str(std::ostream& out) override { out << Name; }

        std::string Name;
};

class ThisObjectNode : public ObjectNode {
    public:
        ThisObjectNode() : ObjectNode() {}
        void Str(std::ostream& out) override { out << "this"; }
};

}} // end namespace 