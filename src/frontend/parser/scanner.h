#pragma once
#include "frontend/ast/ProgramNode.h"

namespace MiniJavab {
namespace Frontend {
namespace Parser {

class ScannerError {
    public:
        ScannerError() {}
};

class ScanResult {
    public:
        ScanResult(MiniJavab::Frontend::AST::ProgramNode* result, MiniJavab::Frontend::Parser::ScannerError* lastError)
            : Result(result),
            LastError(lastError) {}

        MiniJavab::Frontend::AST::Node* Result;
        MiniJavab::Frontend::Parser::ScannerError* LastError;
};

ScanResult* ParseFileToAST(const std::string& f);

}}} // end namespace