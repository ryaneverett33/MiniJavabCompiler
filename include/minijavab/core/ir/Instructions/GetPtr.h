#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a getptr instruction for constructing a pointer value to somewhere in memory
/// @example %0 = getptr vector<i8> @"str.1"
class GetPtrInstruction : public Instruction {
    public:
        /// Create a getptr instruction that constructs a pointer to a global variable
        /// @param variable The variable to construct a pointer to
        /// @param variableType The type of the variable
        /// @param offset A value to offset the constructed pointer by, should point within the global variable
        GetPtrInstruction(IR::Value* variable, IR::Type* variableType, uint32_t offset=0);

        /// @todo is this needed?
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
        /// The variable to construct a pointer ot
        IR::Value* _variable = nullptr;

        /// An optional offset to append to the created pointer
        uint32_t _offset = 0;

        /// @todo is this needed?
        uint32_t _immediate = 0;
};

}}} // end namespace