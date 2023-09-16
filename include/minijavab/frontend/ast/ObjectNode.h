#pragma once
#include "minijavab/frontend/ast/Node.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class ObjectNode : public Node {
    public:
        ObjectNode()
            : Node() {}

        virtual bool IsNamedObject() { return false; }
        virtual bool IsThisObject() { return false; }
        virtual bool IsNewArray() { return false; }
};

class NamedObjectNode : public ObjectNode {
    public:
        NamedObjectNode(std::string name)
            : ObjectNode(),
            Name(name) {}
        void Str(std::ostream& out) override { out << Name; }
        bool IsNamedObject() override { return true; }
        virtual bool IsNewObject() { return false; }

        std::string Name;
};

class ThisObjectNode : public ObjectNode {
    public:
        ThisObjectNode() : ObjectNode() {}
        void Str(std::ostream& out) override { out << "this"; }
        bool IsThisObject() override { return true; }
};

}}} // end namespace 