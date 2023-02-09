#include <gtest/gtest.h>
#include "ast/ast.h"
#include "parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab;

// Demonstrate some basic assertions.
TEST_F(LanguageTests, HelloWorld) {
    AST::Node* tree = Parser::ParseFileToAST(TestDirectory / "hello_world/" / "Program.java");
    EXPECT_NE(tree, nullptr);
}
