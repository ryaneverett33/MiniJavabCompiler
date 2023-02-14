#include <gtest/gtest.h>
#include "frontend/ast/ast.h"
#include "frontend/parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend::Parser;

// Basic test case for `Hello World`
TEST_F(LanguageTests, HelloWorld) {
    ScanResult* result = ParseFileToAST(TestDirectory / "hello_world/" / "Program.java");
    EXPECT_NE(result->Result, nullptr);
}
