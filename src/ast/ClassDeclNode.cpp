#include "ClassDeclNode.h"

namespace MiniJavab {
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

}} // end namespace