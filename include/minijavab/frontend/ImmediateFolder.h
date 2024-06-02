#pragma once
#include "minijavab/frontend/frontend.h"

namespace MiniJavab {
namespace Core {
namespace IR {
    class Immediate;
}} // end Core::IR namespace

namespace Frontend {
namespace ImmediateFolder {

/// Whether or not the expression can be folded into an immediate value
/// @param expression The expression to check
/// @return True if the expression can be folded, false otherwise
bool CanFold(AST::ExpNode* expression);

/// Fold an expression into an immediate value. Caller must check if the expression
/// can be folded before attempting to fold
/// @param expression The expression to fold
/// @return The folded immediate value, never nullptr
Core::IR::Immediate* Fold(AST::ExpNode* expression);

}}} // end namespace