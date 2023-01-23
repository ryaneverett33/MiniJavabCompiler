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
        void Dbg() {}

        ObjectNode* Object;
};

}} // end namespace 