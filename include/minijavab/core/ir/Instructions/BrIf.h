#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {
class BasicBlock;

/// Represents a conditional branch to a control flow block
class BrIfInstruction : public Instruction {
    public:
        /// Create a br instruction to the target basic block
        /// @param target The control flow block to branch to
        /// @param conditional The conditional value to branch against
        BrIfInstruction(IR::BasicBlock* target, IR::Value* conditional);

        bool YieldsValue() const override;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        /// The branch target
        IR::BasicBlock* _targetBlock;

        /// The value to compare against to determine if the branch should be taken
        IR::Value* _conditional;
};

}}} // end namespace