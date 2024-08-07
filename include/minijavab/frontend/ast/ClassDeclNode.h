#pragma once
#include <string>
#include <vector>
#include "minijavab/frontend/ast/Node.h"
#include "minijavab/frontend/ast/VarDeclNode.h"
#include "minijavab/frontend/ast/MethodDeclNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTClass;

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

        /// The symbol table information describing this class
        ASTClass* ClassInfo = nullptr;
};

}}} // end namespace