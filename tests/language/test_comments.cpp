#include <gtest/gtest.h>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"
// TestDirectory fixture is defined here
#include "harness/harness.h"
using namespace MiniJavab::Frontend::Parser;

// Test working `Hello World` with some comments
TEST_F(LanguageTests, Comments_HelloWorld) {
    ScanResult* result = ParseFileToAST(TestDirectory / "hello_world/" / "Program.java");
    EXPECT_NE(result->Result, nullptr);
}

// Test `Hello World` broken with some comments
// Should fail to parse 
TEST_F(LanguageTests, Comments_BrokenHelloWorld) {
    ScanResult* result = ParseFileToAST(TestDirectory / "comments/" / "BrokenProgram.java");
    EXPECT_EQ(result->Result, nullptr);
}
 