#include "minijavab/frontend/ast/VarDeclNode.h"
#include "minijavab/frontend/ast/Node.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

VarDeclNode::VarDeclNode(TypeNode* type, std::string name)
    : Node(),
    Type(type),
    Name(name) {}

VarDeclNode::VarDeclNode(std::string type, std::string name)
    : Node(),
    Name(name) {
    Type = new ObjectTypeNode(type);
}

void VarDeclNode::Str(std::ostream& out) {
    Type->Str(out);
    out << " ";
    out << Name;
}

}}} // end namespace