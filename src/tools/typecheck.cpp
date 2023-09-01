#include <iostream>
#include <string>
#include "frontend/frontend.h"
#include "frontend/TypeChecker.h"

using namespace MiniJavab;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "USAGE: " << argv[0] << ", FILE" << std::endl;
        return 1;
    }

    // parse the AST
    Frontend::AST::Node* tree = Frontend::ParseProgramFile(argv[1]);
    if (tree == nullptr) {
        std::cout << "Failed to parse AST" << std::endl;
        return 1;
    }

    // load the symbol information for typechecking
    Frontend::ASTClassTable* classTable = Frontend::LoadClassTableFromAST(tree);

    // Perform typechecking
    if (Frontend::TypeChecker::Check(dynamic_cast<Frontend::AST::ProgramNode*>(tree), classTable)) {
        std::cout << "Program passed typechecking" << std::endl;
    }
    else {
        std::cout << "Program has errors" << std::endl;
    }
}
