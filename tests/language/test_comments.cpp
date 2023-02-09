#include <gtest/gtest.h>
#include "ast/ast.h"
#include "parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab;

// Test working `Hello World` with some comments
TEST_F(LanguageTests, Comments_HelloWorld) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "hello_world/" / "Program.java");
    EXPECT_NE(tree, nullptr);
}

// Test `Hello World` broken with some comments
// Should fail to parse 
TEST_F(LanguageTests, Comments_BrokenHelloWorld) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "comments/" / "BrokenProgram.java");
    EXPECT_EQ(tree, nullptr);
}
 