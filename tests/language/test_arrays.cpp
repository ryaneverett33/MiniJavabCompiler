#include <gtest/gtest.h>
#include "ast/ast.h"
#include "parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab;

// Test the 2D Array implementation
TEST_F(LanguageTests, Arrays_2DArray) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "arrays/" / "2DArray.java");
    EXPECT_NE(tree, nullptr);
}

// Test the usage of a single dimension array
TEST_F(LanguageTests, Arrays_ArrayUsage) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "arrays/" / "ArrayUsage.java");
    EXPECT_NE(tree, nullptr);
}
