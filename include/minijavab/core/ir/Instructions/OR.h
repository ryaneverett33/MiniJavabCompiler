#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents an OR operation for values X and Y
class ORInstruction : public Instruction {
    public:
        /// Constructs an or instruction
        /// @param x The x value in the OR operation
        /// @param y The y value in the OR operation
        ORInstruction(Value* x, Value* y);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
    private:
        /// The X value of the operation
        Value* _x;
        /// The Y value of the operation
        Value* _y;
};

}}} // end namespace