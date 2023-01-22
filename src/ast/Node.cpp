#include "Node.h"

namespace MiniJavab {
namespace AST {

Node::Node(std::initializer_list<Node*> children) {
    for (Node* child : children) {
        this->children.push_back(child);
    }
}

}}