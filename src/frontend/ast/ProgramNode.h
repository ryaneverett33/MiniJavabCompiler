#pragma once
#include <vector>
#include "Node.h"
#include "ClassDeclNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class ProgramNode : public Node {
    public:
        ProgramNode(ClassDeclNode* mainClass, std::vector<ClassDeclNode*> classes)
            : Node(),
            MainClass(mainClass),
            Classes(classes) {}

        void Dump(std::ostream& out=std::cout) override {
            MainClass->Dump(out);
            if (Classes.size() > 0) {
                for (ClassDeclNode* cls : Classes) {
                    cls->Dump(out);
                }
            }
        }
        void Str(std::ostream& out) override {
            MainClass->Str(out);
            for (ClassDeclNode* classDecl: Classes) {
                classDecl->Str(out);
            }
        }

        ClassDeclNode* MainClass;
        std::vector<ClassDeclNode*> Classes;
};

}}} // end namespace