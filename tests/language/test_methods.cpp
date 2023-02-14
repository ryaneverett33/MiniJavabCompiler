#include <gtest/gtest.h>
#include "frontend/ast/ast.h"
#include "frontend/parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend::Parser;

// Test a program with extension classes
TEST_F(LanguageTests, Methods_ExtensionProgram) {
    ScanResult* result = ParseFileToAST(TestDirectory / "methods/" / "ExtensionProgram.java");
    EXPECT_NE(result->Result, nullptr);
}

// Test a program that utilizes the built-in `.length` method
TEST_F(LanguageTests, Methods_LengthProgram) {
    ScanResult* result = ParseFileToAST(TestDirectory / "methods/" / "LengthProgram.java");
    EXPECT_NE(result->Result, nullptr);
}

// Test a recursive program
TEST_F(LanguageTests, Methods_RecursionProgram) {
    ScanResult* result = ParseFileToAST(TestDirectory / "methods/" / "RecursionProgram.java");
    EXPECT_NE(result->Result, nullptr);
}
