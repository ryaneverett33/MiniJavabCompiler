#pragma once
#include <string>
#include <vector>
#include "minijavab/frontend/ast/Node.h"
#include "minijavab/frontend/ast/TypeNode.h"
#include "minijavab/frontend/ast/VarDeclNode.h"
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
class ASTMethod;

namespace AST {

class MethodDeclNode : public Node {
    public:
        MethodDeclNode(TypeNode* type, std::string name, std::vector<VarDeclNode*> parameters, 
                        std::vector<VarDeclNode*> variables, std::vector<StatementNode*> statements, ExpNode* returnExp);
        void Str(std::ostream& out) override;
        virtual bool IsMainMethod() const { return false; }

        TypeNode* Type;
        std::string Name;
        std::vector<VarDeclNode*> Parameters;
        std::vector<VarDeclNode*> Variables;
        std::vector<StatementNode*> Statements;

        /// The symbol table information describing this method
        ASTMethod* MethodInfo = nullptr;

        /// The value expression being returned by this method.
        /// @note Void-type functions (like `main`) don't have return expressions, so this will be nullptr
        ExpNode* ReturnExp;
};

class MainMethodDeclNode : public MethodDeclNode {
    public:
        MainMethodDeclNode(std::string parameterName, StatementNode* statement)
                        : MethodDeclNode(new VoidTypeNode(), "main", 
                                        { new VarDeclNode(new ArrayTypeNode(new StringTypeNode(), 1), parameterName) }, 
                                        {}, { statement }, nullptr),
                        ParameterName(parameterName),
                        Statement(statement) {}
        bool IsMainMethod() const override { return true; }

        std::string ParameterName;
        StatementNode* Statement;
};

}}} // end namespace