#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents an add instruction
class AddInstruction : public Instruction {
    public:
        /// Constructs an add instruction
        /// @param augend The initial value to be added to
        /// @param addend The operand value to add to the augend
        AddInstruction(Value* augend, Value* addend);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
    private:
        /// The initial value (the left hand side of the add operation)
        Value* _augend;
        /// The value being added to the _augend (the right hand side)
        Value* _addend;
};

}}} // end namespace