#pragma once
#include "ast/Node.h"

namespace MiniJavab {
namespace Parser {

MiniJavab::AST::Node* ParseFileToAST(const std::string& f);

}} // end namespace