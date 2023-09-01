#pragma once
#include <string>
#include <iostream>
#include "ast/ast.h"
#include "ASTClassTable.h"
#include "core/Type.h"

namespace MiniJavab {
namespace Frontend {

// Initialize()
// LoadClassTableFromAST()
// CreateIRModule()
// GetIRLinker()

/// Convert an AST representation of a value type to a Core representation
/// @param node The AST node to convert
/// @return The Core representation of the AST node
/// @see Core::Type
Core::Type* ConvertTypeNodeToType(AST::TypeNode* node);

// Create a Program AST tree from the fileName
AST::Node* ParseProgramFile(std::string fileName, std::ostream& errs=std::cerr);

// TODO: placeholder function for when we support more than programs
/*AST::Node* ParseFileToAST(std::string fileName, std::ostream& errs=std::cerr) {
    // TODO eventually remove `ParseProgramFile` in favor of this method
    return ParseProgramFile(fileName, errs);
}*/

/// Loads class information for a parsed AST
/// @param tree The parsed AST to load information from
/// @return A populated ASTClassTable object
ASTClassTable* LoadClassTableFromAST(AST::Node* tree);

}} // end namespace