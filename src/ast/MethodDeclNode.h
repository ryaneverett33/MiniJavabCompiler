#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "TypeNode.h"
#include "VarDeclNode.h"
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class MethodDeclNode : public Node {
    public:
        MethodDeclNode(TypeNode* type, std::string name, std::vector<VarDeclNode*> parameters, 
                        std::vector<VarDeclNode*> variables, std::vector<StatementNode*> statements, ExpNode* returnExp);
        void Dbg() {};

        TypeNode* Type;
        std::string Name;
        std::vector<VarDeclNode*> Parameters;
        std::vector<VarDeclNode*> Variables;
        std::vector<StatementNode*> Statements;
        ExpNode* ReturnExp;
};

class MainMethodDeclNode : public MethodDeclNode {
    public:
        MainMethodDeclNode(std::string parameterName, StatementNode* statement)
                        : MethodDeclNode(new VoidTypeNode(), "main", {}, {}, {}, {}),
                        ParameterName(parameterName),
                        Statement(statement) {}

        std::string ParameterName;
        StatementNode* Statement;
};

}} // end namespace