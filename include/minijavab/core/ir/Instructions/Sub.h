#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a sub instruction
class SubInstruction : public Instruction {
    public:
        /// Constructs a sub instruction
        /// @param augend The initial value to be subtracted from
        /// @param addend The operand value to subtract from the minuend
        SubInstruction(Value* minuend, Value* subtrahend);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
    private:
        Value* _minuend;
        Value* _subtrahend;
};

}}} // end namespace