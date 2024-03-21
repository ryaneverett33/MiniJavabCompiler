#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a Return Instruction for returning from a function,
/// optionally with a value to return
class RetInstruction : public Instruction {
    public:
        /// Create a return instruction that doesn't return anything
        RetInstruction()
            : Instruction(Opcode::Ret, new IR::VoidType())
            {}

        bool YieldsValue() const override { return false; }
};

}}} // end namespace