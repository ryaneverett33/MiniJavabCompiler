#include <iostream>
#include <string>
#include "minijavab/frontend/frontend.h"
#include "minijavab/frontend/TypeChecker.h"

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
    if (classTable == nullptr) {
        std::cerr << "Program failed to load class table\n";
        return 2;
    }

    // Perform typechecking
    if (Frontend::TypeChecker::Check(dynamic_cast<Frontend::AST::ProgramNode*>(tree), classTable)) {
        std::cout << "Program passed typechecking" << std::endl;
        return 0;
    }
    else {
        std::cout << "Program has errors" << std::endl;
        return 2;
    }
}
