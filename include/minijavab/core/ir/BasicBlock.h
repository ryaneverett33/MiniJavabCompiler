#pragma once
#include <string>
#include <list>

#include "minijavab/core/ir/Instruction.h"
#include "minijavab/core/ir/Function.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a block of instructions with straight control flow.
class BasicBlock : public Value {
    public:
        /// @todo is this needed?
        BasicBlock();

        /// Construct an empty BasicBlock with a given name
        /// @param name The name of the block
        BasicBlock(std::string name);

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

        /// Append a newly constructed instruction to the list of instructions
        /// @param instruction The instruction to append
        void AppendInstruction(Instruction* instruction);

        /// Position of this basic block in the parent function's list of basic
        /// blocks
        std::list<BasicBlock*>::iterator Position;

        /// List of instructions in this basic block
        std::list<Instruction*> Instructions;

        /// The Function containing this Basic Block
        Function* ParentFunction = nullptr;
};

}}} // end namespace