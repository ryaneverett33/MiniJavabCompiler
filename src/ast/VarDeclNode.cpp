#include "VarDeclNode.h"
#include "Node.h"

namespace MiniJavab {
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

}} // end namespace