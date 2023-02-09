#pragma once

#include <string>
#include <map>
#include "parser.h"
#include "ast/Node.h"

#define YY_DECL \
  yy::parser::symbol_type yylex (ParserDriver& driver)
YY_DECL;

class ParserDriver {
 public:
    ParserDriver() :
      IsScanning(false),
      Result(nullptr) {}
    void ScanFile(std::string filePath);
    void ScanStandardInput();
    void FinishScanning();

    bool IsScanning;
    MiniJavab::AST::ProgramNode* Result;
    yy::location CurrentLocation;
};