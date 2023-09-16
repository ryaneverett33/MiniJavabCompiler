#pragma once
#include "minijavab/frontend/ast/StatementNode.h"
#include "minijavab/frontend/ast/ExpNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

class PrintStatementNode : public StatementNode {
    public:
        PrintStatementNode(bool newLine=false)
        : StatementNode(StatementKind::Print),
        NewLine(newLine) {}
        virtual bool IsPrintStringStatement() { return false; }
        virtual bool IsPrintExpressionStatement() { return false; }

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

class PrintStringStatementNode : public PrintStatementNode {
    public:
        PrintStringStatementNode(std::string string, bool newLine=false)
        : PrintStatementNode(newLine),
        String(string) {}
        
        void Str(std::ostream& out) override {
            PrintStatementNode::MethodStr(out);
            out << "(" << "\"" << String << "\";";
        }
        bool IsPrintStringStatement() override { return true; }

        std::string String;
};

class PrintExpStatementNode : public PrintStatementNode {
    public:
        PrintExpStatementNode(ExpNode* expression, bool newLine=false)
        : PrintStatementNode(newLine),
        Expression(expression) {}

        void Str(std::ostream& out) override {
            PrintStatementNode::MethodStr(out);
            out << "(";
            Expression->Str(out);
            out << ");";
        }
        bool IsPrintExpressionStatement() override { return true; }

        ExpNode* Expression;
};

}}} // end namespace