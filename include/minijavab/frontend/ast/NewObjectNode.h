#pragma once
#include <string>
#include "minijavab/frontend/ast/ObjectNode.h"
#include "minijavab/frontend/ast/TypeNode.h"
#include "minijavab/frontend/ast/IndexNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTVariable;

namespace AST {

class NewObjectNode : public NamedObjectNode {
    public:
        NewObjectNode(std::string name)
            : NamedObjectNode(name) {}
        void Str(std::ostream& out) override {
            out << "new " << Name << "()";
        }
        virtual bool IsNewObject() override { return true; }

        /// Class Info about the object being created
        ASTClass* ObjectInfo = nullptr;
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

        /// Class Info about the object being created
        ASTClass* ObjectInfo = nullptr;
};

}}} // end namespace 