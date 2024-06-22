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

        ObjectNode* Object;
        std::string Method;
        std::vector<ExpNode*> Expressions;

        /// The method that's being called
        ASTMethod* CalledMethod = nullptr;
};

}}} // end namespace 