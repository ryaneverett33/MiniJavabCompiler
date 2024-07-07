#pragma once
#include <iostream>
#include "minijavab/frontend/ASTClassTable.h"
#include "minijavab/frontend/ast/ast.h"

namespace MiniJavab {
namespace Frontend {
namespace TypeChecker {

/// Perform typechecking on the program AST, reporting errors if they occur
/// @param program The program tree to perform checking on
/// @param table AST Symbol table
/// @param errs Output stream to write errors to
/// @return True if typechecking succeeded without errors, False if there were errors in the AST
bool Check(AST::ProgramNode* const program, ASTClassTable* const table, std::ostream& errs=std::cerr);

}}} // end namespace