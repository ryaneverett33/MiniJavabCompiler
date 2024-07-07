#include <gtest/gtest.h>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"
#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/TypeChecker.h"
// TestDirectory fixture is defined here
#include "harness/harness.h"
using namespace MiniJavab::Frontend;

// Test a program with extension classes
TEST_F(LanguageTests, Objects_ExtensionProgram) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "objects/" / "ExtensionProgram.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(classTable != nullptr);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

// Test a program that utilizes the built-in `.length` method
TEST_F(LanguageTests, Objects_LengthProgram) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "objects/" / "LengthProgram.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(classTable != nullptr);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

// Test a recursive program
TEST_F(LanguageTests, Objects_RecursionProgram) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "objects/" / "RecursionProgram.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(classTable != nullptr);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

TEST_F(LanguageTests, Objects_Errors) {
    auto loadAndCheckFile = [](std::filesystem::path path) {
        Parser::ScanResult* result = Parser::ParseFileToAST(path);
        ASSERT_NE(result->Result, nullptr);

        AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
        ASTClassTable* classTable = LoadClassTableFromAST(program);
        ASSERT_FALSE(classTable != nullptr);
        ASSERT_FALSE(TypeChecker::Check(program, classTable));
    };
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "objects/" / "errors/" / "IntegerLength.java");
    ASSERT_EQ(result->Result, nullptr);
    result = Parser::ParseFileToAST(TestDirectory / "objects/" / "errors/" / "DeclaringClassString.java");
    ASSERT_EQ(result->Result, nullptr);
}