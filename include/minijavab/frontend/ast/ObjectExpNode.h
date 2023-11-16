#pragma once
#include <string>
#include "minijavab/frontend/ast/ExpNode.h"
#include "minijavab/frontend/ast/ObjectNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class ObjectExpNode : public ExpNode {
    public:
        ObjectExpNode(ObjectNode* object)
            : ExpNode(ExpKind::Object),
            Object(object) {}
        void Str(std::ostream& out) override { Object->Str(out); }

        ObjectNode* Object;
};

}}} // end namespace 