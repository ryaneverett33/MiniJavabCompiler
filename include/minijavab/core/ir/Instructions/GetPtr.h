#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {
class GlobalVariable;

/// Represents a load Instruction for loading memory from a pointer
class GetPtrInstruction : public Instruction {
    public:
        /// Create a getptr instruction that constructs a pointer to a global
        /// variable
        /// @param variable
        GetPtrInstruction(IR::GlobalVariable* variable);

        /// Create a getptr instruction that constructs a pointer with a constant value
        /// @note Useful for creating null values
        /// @todo
        GetPtrInstruction(IR::Type* type, uint32_t immediate);

        /// Whether or not this instruction is constructed from, and references, a
        /// global variable
        /// @see Opcode::GetPtrValue
        /// @return True if the constructed pointer points to a global variable, false
        /// otherwise
        bool ReferencesGlobalVariable() const;

        /// Whether or not this instruction is constructed from an immediate value
        /// @see Opcode::GetPtrImmediate
        /// @return True if the constructed pointer is a known immediate value, false
        /// otherwise
        bool IsImmediatePointer() const;

        bool YieldsValue() const override { return true; }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        IR::GlobalVariable* _variable = nullptr;
        uint32_t _immediate = 0;
};

}}} // end namespace