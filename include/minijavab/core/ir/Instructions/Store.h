#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a Store Instruction for storing values into memory
class StoreInstruction : public Instruction {
    public:
        /// Create a store instruction storing object into memory
        /// pointed to by pointer
        /// @param object The object to store
        /// @param pointer Pointer to memory
        StoreInstruction(Value* object, Value* pointer);

        bool YieldsValue() const override { return false; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        /// The value being stored
        Value* _object;

        /// Where to store the value
        Value* _pointer;
};

}}} // end namespace