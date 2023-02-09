#pragma once
#include <string>
#include "ExpNode.h"
#include "ObjectNode.h"

namespace MiniJavab {
namespace AST {

class ObjectExpNode : public ExpNode {
    public:
        ObjectExpNode(ObjectNode* object)
            : ExpNode(),
            Object(object) {}
        void Str(std::ostream& out) override { Object->Str(out); }

        ObjectNode* Object;
};

}} // end namespace 