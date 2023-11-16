#include <gtest/gtest.h>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"
#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/TypeChecker.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend;

// Test a program with extension classes
TEST_F(LanguageTests, Methods_ExtensionProgram) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "methods/" / "ExtensionProgram.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

// Test a program that utilizes the built-in `.length` method
TEST_F(LanguageTests, Methods_LengthProgram) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "methods/" / "LengthProgram.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

// Test a recursive program
TEST_F(LanguageTests, Methods_RecursionProgram) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "methods/" / "RecursionProgram.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}
