#pragma once
#include <string>
#include <list>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Instructions/Opcodes.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock;

/// Represents a single instruction contained with a Basic Block
class Instruction : public Value {
    public:
        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        virtual void Print(std::ostream& out = std::cerr) const;

        /// Whether or not this instruction returns a value for immediate usage
        /// @returns True if this instruction returns a value, else False
        virtual bool YieldsValue() const = 0;

        /// The position of this instruction within the parent Basic Block
        /// @see ParentBlock
        std::list<Instruction*>::iterator Position;
        
        /// The parent Basic Block that contains this instruction
        BasicBlock* ParentBlock = nullptr;

    protected:
        /// Construct a new instruction with a given Opcode and Type. The type
        /// is determined as the potentially yielded type.
        /// @param opcode The opcode of this instruction
        /// @param type The type this instruction potentially yields. Instructions
        /// that don't yield a value have a void type. Instructions that yield a value,
        /// like an add instruction, will have the same type as their yielded value.
        Instruction(Opcode opcode, IR::Type* type);

        /// The Opcode for this instruction
        Opcode _opcode;
};

}}} // end namespace