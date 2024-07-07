#pragma once
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class PrintStatementNode : public StatementNode {
    public:
        PrintStatementNode(ExpNode* expression, bool newLine=false)
            : StatementNode(StatementKind::Print),
            Expression(expression),
            NewLine(newLine) {}

        void Str(std::ostream& out) override {
            if (NewLine) {
                out << "System.out.println";
            }
            else {
                out << "System.out.print";
            }

            out << "(";
            Expression->Str(out);
            out << ");";
        }

        ExpNode* Expression;
        bool NewLine;
    protected:
        void MethodStr(std::ostream& out) {
            if (NewLine) {
                out << "System.out.println";
            }
            else {
                out << "System.out.print";
            }
        }
};

}}} // end namespace