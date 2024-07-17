#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {
class BasicBlock;

/// Represents an unconditional branch to a control flow block
class BrInstruction : public Instruction {
    public:
        /// Create a br instruction to the target basic block
        /// @param target The control flow block to branch to
        BrInstruction(IR::BasicBlock* target);

        bool YieldsValue() const override;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        IR::BasicBlock* _targetBlock;
};

}}} // end namespace