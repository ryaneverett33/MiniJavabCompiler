#include <gtest/gtest.h>
#include "frontend/ast/ast.h"
#include "frontend/parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend::Parser;

// Test a program with if-else statements
TEST_F(LanguageTests, Statements_IfElse) {
    ScanResult* result = ParseFileToAST(TestDirectory / "statements/" / "IfElse.java");
    EXPECT_NE(result->Result, nullptr);
}

// Test a program containing a while-loop
TEST_F(LanguageTests, Statements_WhileLoop) {
    ScanResult* result = ParseFileToAST(TestDirectory / "statements/" / "WhileLoop.java");
    EXPECT_NE(result->Result, nullptr);
}
