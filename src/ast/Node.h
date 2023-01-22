#pragma once
#include <vector>
#include <initializer_list>

namespace MiniJavab {
namespace AST {

class Node {
    public:
        Node(std::initializer_list<Node*> children);
        virtual void Dbg() = 0;

    protected:
        std::vector<Node*> children;
};

}
}