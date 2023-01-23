#include "MethodDeclNode.h"

namespace MiniJavab {
namespace AST {

MethodDeclNode::MethodDeclNode(TypeNode* type, std::string name, std::vector<VarDeclNode*> parameters,
                                std::vector<VarDeclNode*> variables, std::vector<StatementNode*> statements, ExpNode* returnExp) :
                            Node(),
                            Type(type),
                            Name(name),
                            Parameters(parameters),
                            Variables(variables),
                            Statements(statements),
                            ReturnExp(returnExp) {}

}} // end namespace