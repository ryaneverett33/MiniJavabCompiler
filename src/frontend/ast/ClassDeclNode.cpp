#include "minijavab/frontend/ast/ClassDeclNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

ClassDeclNode::ClassDeclNode(std::string name, std::vector<VarDeclNode*> variables, 
                            std::vector<MethodDeclNode*> methods)
                        : Node(),
                        IsExtensionClass(false),
                        Name(name),
                        BaseClass(""),
                        Variables(variables),
                        Methods(methods) {}

ClassDeclNode::ClassDeclNode(std::string name, std::string baseClass, 
                            std::vector<VarDeclNode*> variables, std::vector<MethodDeclNode*> methods)
                        : Node(),
                        IsExtensionClass(true),
                        Name(name),
                        BaseClass(baseClass),
                        Variables(variables),
                        Methods(methods) {}

void ClassDeclNode::Str(std::ostream& out) {
    out << "class " << Name;
    if (IsExtensionClass) { out << " extends " << BaseClass; }
    out << " {" << std::endl;
    if (Variables.size() > 0) {
        for (VarDeclNode* variable : Variables) {
            variable->Str(out);
            out << std::endl;
        }
        if (Methods.size() > 0) { out << std::endl; }
    }
    if (Methods.size() > 0) {
        for (MethodDeclNode* method : Methods) {
            method->Dump(out);
        }
    }
    out << "}" << std::endl;
}

}}} // end namespace