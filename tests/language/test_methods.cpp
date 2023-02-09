#include <gtest/gtest.h>
#include "ast/ast.h"
#include "parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab;

// Test a program with extension classes
TEST_F(LanguageTests, Methods_ExtensionProgram) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "methods/" / "ExtensionProgram.java");
    EXPECT_NE(tree, nullptr);
}

// Test a program that utilizes the built-in `.length` method
TEST_F(LanguageTests, Methods_LengthProgram) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "methods/" / "LengthProgram.java");
    EXPECT_NE(tree, nullptr);
}

// Test a recursive program
TEST_F(LanguageTests, Methods_RecursionProgram) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "methods/" / "RecursionProgram.java");
    EXPECT_NE(tree, nullptr);
}
