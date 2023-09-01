#pragma once
#include <string>
#include <vector>
#include "Node.h"
#include "TypeNode.h"
#include "VarDeclNode.h"
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class MethodDeclNode : public Node {
    public:
        MethodDeclNode(TypeNode* type, std::string name, std::vector<VarDeclNode*> parameters, 
                        std::vector<VarDeclNode*> variables, std::vector<StatementNode*> statements, ExpNode* returnExp);
        void Str(std::ostream& out) override;

        TypeNode* Type;
        std::string Name;
        std::vector<VarDeclNode*> Parameters;
        std::vector<VarDeclNode*> Variables;
        std::vector<StatementNode*> Statements;

        /// The value expression being returned by this method.
        /// @note Void-type functions (like `main`) don't have return expressions, so this will be nullptr
        ExpNode* ReturnExp;
};

class MainMethodDeclNode : public MethodDeclNode {
    public:
        MainMethodDeclNode(std::string parameterName, StatementNode* statement)
                        : MethodDeclNode(new VoidTypeNode(), "main", 
                                        { new VarDeclNode(new StringTypeNode(), parameterName) }, 
                                        {}, { statement }, nullptr),
                        ParameterName(parameterName),
                        Statement(statement) {}

        std::string ParameterName;
        StatementNode* Statement;
};

}}} // end namespace