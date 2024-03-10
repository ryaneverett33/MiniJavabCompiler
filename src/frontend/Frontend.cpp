#include "minijavab/frontend/frontend.h"

#include <cassert>

#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"
#include "minijavab/frontend/TypeChecker.h"
#include "minijavab/frontend/Converter.h"

#include "minijavab/core/ir/Module.h"

namespace MiniJavab {
namespace Frontend {

AST::Node* ParseProgramFile(std::filesystem::path fileName, std::ostream& errs) {
    Parser::ScanResult* result = Parser::ParseFileToAST(fileName);
    if (result->Result == nullptr) {
        // print errors to the error stream
        // TODO
        errs << "Encountered errors parsing: " << fileName << std::endl;
    }
    return result->Result;
}

ASTClassTable* LoadClassTableFromAST(AST::Node* tree) {
    assert(tree != nullptr && "Called LoadClassTableFromAST with a null argument");

    if (AST::ProgramNode* programNode = dynamic_cast<AST::ProgramNode*>(tree)) {
        ASTClassTable* table = new ASTClassTable();
        table->AddClass(programNode->MainClass);

        for (AST::ClassDeclNode* classDecl: programNode->Classes) {
            table->AddClass(classDecl);
        }
        table->Finalize();
        return table;
    }
    else {
        assert(false && "Invalid ast type");
        return nullptr; // unreachable
    }
}

Core::IR::Module* LoadProgramFile(std::filesystem::path fileName, std::ostream& errs) {
    // Load AST
    AST::Node* tree = ParseProgramFile(fileName, errs);
    if (tree == nullptr) { return nullptr; }

    // Load class information
    ASTClassTable* table = LoadClassTableFromAST(tree);
    if (table == nullptr) { return nullptr; }

    // Perform typechecking
    if (!TypeChecker::Check(static_cast<AST::ProgramNode*>(tree), table, errs)) { return nullptr; }

    return ASTConverter::Convert(static_cast<AST::ProgramNode*>(tree), table, fileName.filename());
}

}} // end namespace