#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents an Allocation Instruction for allocating space for a local variable
class AllocInstruction : public Instruction {
    public:
        /// Create a alloc instruction that allocates space for a given type
        /// @param localType The type to allocate space for/the local variable type
        /// @param name The name of the yielded value/local variable
        AllocInstruction(IR::Type* localType, std::string name);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace