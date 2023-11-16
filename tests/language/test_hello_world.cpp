#include <gtest/gtest.h>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"
#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/TypeChecker.h"
// TestDirectory fixture is defined here
#include "common.h"
using namespace MiniJavab::Frontend;

// Basic test case for `Hello World`
TEST_F(LanguageTests, HelloWorld) {
    Parser::ScanResult* result = Parser::ParseFileToAST(TestDirectory / "hello_world/" / "Program.java");
    ASSERT_NE(result->Result, nullptr);

    AST::ProgramNode* program = static_cast<AST::ProgramNode*>(result->Result);
    ASTClassTable* classTable = LoadClassTableFromAST(program);
    ASSERT_TRUE(TypeChecker::Check(program, classTable));
}
