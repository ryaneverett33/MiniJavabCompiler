#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents an add instruction
class AddInstruction : public Instruction {
    public:
        /// Constructs an add instruction
        /// @param arg1 The initial value operand for the add operation
        /// @param arg2 The second value or immediate operand for the add operation 
        AddInstruction(Value* arg1, Value* arg2);

        bool YieldsValue() const override { return true; }
};

}}} // end namespace