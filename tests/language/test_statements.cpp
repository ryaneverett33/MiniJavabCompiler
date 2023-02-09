#include <gtest/gtest.h>
#include "ast/ast.h"
#include "parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab;

// Test a program with if-else statements
TEST_F(LanguageTests, Statements_IfElse) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "statements/" / "IfElse.java");
    EXPECT_NE(tree, nullptr);
}

// Test a program containing a while-loop
TEST_F(LanguageTests, Statements_WhileLoop) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "statements/" / "WhileLoop.java");
    EXPECT_NE(tree, nullptr);
}
