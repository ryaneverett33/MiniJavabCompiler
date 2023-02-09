#include <gtest/gtest.h>
#include "ast/ast.h"
#include "parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab;

// Basic test case for `Hello World`
TEST_F(LanguageTests, HelloWorld) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "hello_world/" / "Program.java");
    EXPECT_NE(tree, nullptr);
}
