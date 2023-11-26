#include <gtest/gtest.h>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"
#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/TypeChecker.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend;

// Test a program with if-else statements
TEST_F(LanguageTests, Statements_IfElse) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "statements/" / "IfElse.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

// Test a program containing a while-loop
TEST_F(LanguageTests, Statements_WhileLoop) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "statements/" / "WhileLoop.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

TEST_F(LanguageTests, Statements_errors) {
    auto loadAndCheckFile = [](std::filesystem::path path) {
        Parser::ScanResult* result = Parser::ParseFileToAST(path);
        ASSERT_NE(result->Result, nullptr);

        AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
        ASTClassTable* classTable = LoadClassTableFromAST(program);
        ASSERT_FALSE(TypeChecker::Check(program, classTable));
    };
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "statements/" / "errors/" / "ElseOneBracket.java");
    ASSERT_EQ(result->Result, nullptr);
    loadAndCheckFile(TestDirectory / "statements/" / "errors/" / "DuplicateLocalVar.java");
}