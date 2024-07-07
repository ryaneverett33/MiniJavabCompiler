#pragma once
#include <string>
#include <iostream>
#include <filesystem>

#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/ASTClassTable.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class Module;
}} // end namespace Core/IR

namespace Frontend {

// Initialize()
// LoadClassTableFromAST()
// CreateIRModule()
// GetIRLinker()

// Create a Program AST tree from the fileName
AST::Node* ParseProgramFile(std::filesystem::path fileName, std::ostream& errs=std::cerr);

// TODO: placeholder function for when we support more than programs
/*AST::Node* ParseFileToAST(std::string fileName, std::ostream& errs=std::cerr) {
    // TODO eventually remove `ParseProgramFile` in favor of this method
    return ParseProgramFile(fileName, errs);
}*/

/// Loads class information for a parsed AST
/// @param tree The parsed AST to load information from
/// @param errs An output stream for reporting error messages
/// @return A populated ASTClassTable object
ASTClassTable* LoadClassTableFromAST(AST::Node* tree, std::ostream& errs=std::cerr);

Core::IR::Module* LoadProgramFile(std::filesystem::path fileName, std::ostream& errs=std::cerr);

}} // end namespace