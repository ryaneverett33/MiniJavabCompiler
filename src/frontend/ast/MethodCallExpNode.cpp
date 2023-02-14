#include "MethodCallExpNode.h"
#include "ObjectNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

void MethodCallExpNode::Str(std::ostream& out) {
    Object->Str(out);
    out << "." << Method << "(";
    for (int expressionIndex = 0; expressionIndex < Expressions.size(); expressionIndex++) {
        ExpNode* expression = Expressions[expressionIndex];
        expression->Str(out);

        if ((expressionIndex + 1) < Expressions.size()) {
            out << ",";
        }
    }
    out << ")";
}

}}} // end namespace