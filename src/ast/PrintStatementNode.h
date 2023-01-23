#pragma once
#include "StatementNode.h"
#include "ExpNode.h"

namespace MiniJavab {
namespace AST {

class PrintStatementNode : public StatementNode {
    public:
        PrintStatementNode(std::string string, bool newLine=false)
        : StatementNode(),
        String(string),
        NewLine(newLine) {}
        void Dbg() {};

        std::string String;
        bool NewLine;
};

class PrintExpStatementNode : public StatementNode {
    public:
        PrintExpStatementNode(ExpNode* expression, bool newLine=false)
        : StatementNode(),
        Expression(expression),
        NewLine(newLine) {}
        void Dbg() {};

        ExpNode* Expression;
        bool NewLine;
};

}} // end namespace