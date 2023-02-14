#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "VarDeclNode.h"
#include "MethodDeclNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class ClassDeclNode : public Node {
    public:
        ClassDeclNode(std::string name, std::vector<VarDeclNode*> variables, std::vector<MethodDeclNode*> methods);
        ClassDeclNode(std::string name, std::string baseClass, std::vector<VarDeclNode*> variables, std::vector<MethodDeclNode*> methods);

        bool IsExtensionClass;
        std::string Name;
        std::string BaseClass;
        std::vector<VarDeclNode*> Variables;
        std::vector<MethodDeclNode*> Methods;

        void Str(std::ostream& out) override;
};

}}} // end namespace