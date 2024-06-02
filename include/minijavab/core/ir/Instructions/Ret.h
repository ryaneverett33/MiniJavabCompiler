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
        RetInstruction();
        
        /// Create a return instruction that returns a value
        /// @param returnValue The value to return
        RetInstruction(IR::Value* returnValue);

        bool YieldsValue() const override { return false; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
    private:
        IR::Value* _returnValue = nullptr;
};

}}} // end namespace