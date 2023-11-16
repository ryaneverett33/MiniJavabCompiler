#include <iostream>
#include <string>
#include "minijavab/frontend/ast/ast.h"
#include "minijavab/frontend/parser/scanner.h"

using namespace MiniJavab::Frontend;

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "USAGE: " << argv[0] << ", FILE" << std::endl;
    return 1;
  }

  Parser::ScanResult* result = Parser::ParseFileToAST(argv[1]);
  AST::Node* tree = result->Result;
  if (tree == nullptr) {
    std::cout << "Failed to parse AST" << std::endl;
    return 1;
  }
  std::cout << "AST:" << std::endl;
  tree->Dump();
  return 0;
}
