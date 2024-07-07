#pragma once
#include <vector>
#include "minijavab/frontend/ast/ExpNode.h"
#include "minijavab/frontend/ast/ObjectNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTMethod;

namespace AST {


class MethodCallExpNode : public ExpNode {
    public:
        MethodCallExpNode(std::string objectName, std::string method, std::vector<ExpNode*> expressions)
            : ExpNode(ExpKind::MethodCall),
            Method(method),
            Expressions(expressions) {
                Object = new NamedObjectNode(objectName);
        }
        MethodCallExpNode(ObjectNode* object, std::string method, std::vector<ExpNode*> expressions)
            : ExpNode(ExpKind::MethodCall),
            Object(object),
            Method(method),
            Expressions(expressions) {}
        void Str(std::ostream& out) override;

        /// The object whose method is being called
        ObjectNode* Object;

        /// The name of the method being called
        std::string Method;

        /// Parameters to pass to the method invocation
        std::vector<ExpNode*> Expressions;

        /// The method that's being called
        ASTMethod* CalledMethod = nullptr;
};

}}} // end namespace 