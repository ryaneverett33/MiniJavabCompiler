#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a load Instruction for loading memory from a pointer
class LoadInstruction : public Instruction {
    public:
        /// Create a load instruction that loads memory of a given type from a pointer
        /// @param type The type of the memory to load
        /// @param pointer The pointer to the memory to load
        LoadInstruction(IR::Type* type, IR::Value* pointer);

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        IR::Value* _pointer;
};

}}} // end namespace