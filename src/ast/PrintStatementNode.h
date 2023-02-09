#pragma once
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class PrintStatementNode : public StatementNode {
    public:
        PrintStatementNode(bool newLine=false)
        : StatementNode(),
        NewLine(newLine) {}

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

        ExpNode* Expression;
};

}} // end namespace