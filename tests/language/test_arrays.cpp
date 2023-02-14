#include <gtest/gtest.h>
#include "frontend/ast/ast.h"
#include "frontend/parser/scanner.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend::Parser;

// Test the 2D Array implementation
TEST_F(LanguageTests, Arrays_2DArray) {
    ScanResult* result = ParseFileToAST(TestDirectory / "arrays/" / "2DArray.java");
    EXPECT_NE(result->Result, nullptr);
}

// Test the usage of a single dimension array
TEST_F(LanguageTests, Arrays_ArrayUsage) {
    ScanResult* result = ParseFileToAST(TestDirectory / "arrays/" / "ArrayUsage.java");
    EXPECT_NE(result->Result, nullptr);
}
