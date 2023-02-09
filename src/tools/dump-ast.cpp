#include <iostream>
#include <string>
#include "ast/ast.h"
#include "parser/scanner.h"
#define YYDEBUG 1

using namespace MiniJavab;

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cout << "USAGE: " << argv[0] << ", FILE" << std::endl;
    return 1;
  }

  AST::ProgramNode* tree = dynamic_cast<AST::ProgramNode*>(Parser::ParseFileToAST(argv[1]));
  if (tree == nullptr) {
    std::cout << "Failed to parse AST" << std::endl;
    return 1;
  }
  std::cout << "AST:" << std::endl;
  tree->Dump(std::cout);
  return 0;
}
