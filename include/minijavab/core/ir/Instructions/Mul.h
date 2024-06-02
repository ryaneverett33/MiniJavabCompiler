#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a mul instruction
class MulInstruction : public Instruction {
    public:
        /// Constructs a mul instruction
        /// @param multiplicand The initial value to be multiplied
        /// @param multiplier The multiplier value to multiply the multiplicand by
        MulInstruction(Value* multiplicand, Value* multiplier);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
    private:
        /// The value to be multiplied
        Value* _multiplicand;

        /// The value to multiply the multiplicand by
        Value* _multiplier;
};

}}} // end namespace