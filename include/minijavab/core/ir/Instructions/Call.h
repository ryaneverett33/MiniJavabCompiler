#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {
class Function;

/// Represents a call to a function which temporarily redirects control flow to
/// the callee function.
class CallInstruction : public Instruction {
    public:
        /// Create a call instruction to the function with a given set of arguments
        /// @param function The function to call
        /// @param arguments Arguments to call the function with
        CallInstruction(IR::Function* function, std::vector<IR::Value*> arguments);

        bool YieldsValue() const override;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        IR::Function* _calleeFunction;
        std::vector<IR::Value*> _arguments;
};

}}} // end namespace