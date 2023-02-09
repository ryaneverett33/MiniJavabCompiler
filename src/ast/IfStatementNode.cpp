#include "IfStatementNode.h"
#include "ObjectNode.h"

namespace MiniJavab {
namespace AST {

void IfStatementNode::Str(std::ostream& out) {
    out << "if (";
    Expression->Str(out);
    out << ") {" << std::endl;
    IfStatement->Str(out);
    out << std::endl;
    out << "}" << std::endl;
    out << "else {" << std::endl;
    ElseStatement->Str(out);
    out << std::endl;
    out << "}";
}

}} // end namespace