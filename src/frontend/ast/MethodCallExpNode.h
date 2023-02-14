#pragma once
#include <vector>
#include "ExpNode.h"
#include "ObjectNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class MethodCallExpNode : public ExpNode {
    public:
        MethodCallExpNode(std::string objectName, std::string method, std::vector<ExpNode*> expressions)
            : ExpNode(),
            Method(method),
            Expressions(expressions) {
                Object = new NamedObjectNode(objectName);
        }
        MethodCallExpNode(ObjectNode* object, std::string method, std::vector<ExpNode*> expressions)
            : ExpNode(),
            Object(object),
            Method(method),
            Expressions(expressions) {}
        void Str(std::ostream& out) override;

        ObjectNode* Object;
        std::string Method;
        std::vector<ExpNode*> Expressions;
};

}}} // end namespace 