#include "common.h"

#include "minijavab/frontend/ast/ast.h"
#include "scanner.h"
#include "minijavab/frontend/TypeChecker.h"
#include "minijavab/frontend/frontend.h"

#include <gtest/gtest.h>

#include <iostream>

using namespace MiniJavab::Frontend;

// Test the 2D Array implementation
TEST_F(LanguageTests, Arrays_2DArray) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "arrays/" / "2DArray.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}

// Test the usage of a single dimension array
TEST_F(LanguageTests, Arrays_ArrayUsage) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "arrays/" / "ArrayUsage.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}