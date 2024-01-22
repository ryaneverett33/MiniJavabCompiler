#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"

namespace MiniJavab {
namespace Frontend {

AST::Node* ParseProgramFile(std::string fileName, std::ostream& errs) {
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

}} // end namespace