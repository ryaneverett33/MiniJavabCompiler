#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents an Allocation Instruction for allocating space for a local variable
class AllocInstruction : public Instruction {
    public:
        
        AllocInstruction(IR::Type* localType, std::string name);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace