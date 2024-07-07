#pragma once
#include "minijavab/frontend/ast/Node.h"

namespace MiniJavab {
namespace Frontend {
class ASTClass;
class ASTVariable;

namespace AST {

class ObjectNode : public Node {
    public:
        ObjectNode()
            : Node() {}

        virtual bool IsNamedObject() { return false; }
        virtual bool IsThisObject() { return false; }
        virtual bool IsNewArray() { return false; }

        /// Class information about this object
        ASTClass* ClassInfo = nullptr;
};

class NamedObjectNode : public ObjectNode {
    public:
        NamedObjectNode(std::string name)
            : ObjectNode(),
            Name(name) {}
        void Str(std::ostream& out) override { out << Name; }
        bool IsNamedObject() override { return true; }
        virtual bool IsNewObject() { return false; }

        /// The symbol being referenced
        ASTVariable* Symbol = nullptr;

        /// The name of the symbol
        std::string Name;
};

class ThisObjectNode : public ObjectNode {
    public:
        ThisObjectNode() : ObjectNode() {}
        void Str(std::ostream& out) override { out << "this"; }
        bool IsThisObject() override { return true; }

        /// The symbol being referenced
        ASTVariable* Symbol = nullptr;
};

}}} // end namespace 