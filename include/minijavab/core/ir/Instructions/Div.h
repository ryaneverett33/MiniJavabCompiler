#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a div instruction
class DivInstruction : public Instruction {
    public:
        /// Constructs a div instruction
        /// @param dividend The initial value to be divided
        /// @param divisor The operand value to divide the dividend by
        DivInstruction(Value* dividend, Value* divisor);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
    private:
        /// The value to be divided
        Value* _dividend;
        /// The value to divide by
        Value* _divisor;
};

}}} // end namespace