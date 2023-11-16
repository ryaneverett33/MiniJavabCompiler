#pragma once
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class WhileStatementNode : public StatementNode {
    public:
        WhileStatementNode(ExpNode* expression, StatementNode* statement)
        : StatementNode(StatementKind::While),
        Expression(expression),
        Statement(statement) {}
        void Str(std::ostream& out) override {
            out << "while(";
            Expression->Str(out);
            out << ") {" << std::endl;
            Statement->Str(out);
            out << std::endl << "}";
        }

        ExpNode* Expression;
        StatementNode* Statement;
};

}}} // end namespace