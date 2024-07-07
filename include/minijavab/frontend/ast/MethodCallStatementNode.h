#pragma once
#include <vector>
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/MethodCallExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

/// Represents a method invocation that doesn't return any values
class MethodCallStatementNode : public StatementNode {
    public:
        MethodCallStatementNode(MethodCallExpNode* methodCallExpression)
        : StatementNode(StatementKind::MethodCall),
        CallExpression(methodCallExpression) {}

        void Str(std::ostream& out) override {
            CallExpression->Str(out);
        }

        /// The method invocation expression
        MethodCallExpNode* CallExpression;
};

}}} // end namespace