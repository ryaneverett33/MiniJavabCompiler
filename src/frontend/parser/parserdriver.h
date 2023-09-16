#pragma once

#include <string>
#include <map>
#include "parser.h"
#include "minijavab/frontend/ast/Node.h"

#define YY_DECL \
    yy::parser::symbol_type yylex (ParserDriver& driver)
YY_DECL;

class Error {
    public:
        Error(std::string message, yy::location location) :
            Message(message),
            Location(location) {}

        std::string Message;
        yy::location Location;
};

class ParserDriver {
    public:
        ParserDriver() :
            IsScanning(false),
            Result(nullptr),
            LastError(nullptr) {}
        void ScanFile(std::string filePath);
        void ScanStandardInput();
        bool FinishScanning();

        bool IsScanning;
        MiniJavab::Frontend::AST::ProgramNode* Result;
        Error* LastError;
        yy::location CurrentLocation;
};