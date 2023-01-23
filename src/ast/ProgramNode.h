#pragma once
#include <vector>
#include "Node.h"
#include "ClassDeclNode.h"

namespace MiniJavab {
namespace AST {

class ProgramNode : public Node {
    public:
        ProgramNode(ClassDeclNode* mainClass, std::vector<ClassDeclNode*> classes)
            : Node(),
            MainClass(mainClass),
            Classes(classes) {}

        void Dbg() {}

        ClassDeclNode* MainClass;
        std::vector<ClassDeclNode*> Classes;
};

}} // end namespace