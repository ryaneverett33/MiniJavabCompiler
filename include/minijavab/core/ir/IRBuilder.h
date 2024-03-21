#pragma once

#include "minijavab/core/ir/BasicBlock.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {

/// An IRBuilder is a helper object for easily creating and inserting instructions
/// into a Basic Block. Instructions created through an IRBuilder are automatically
/// inserted into the Basic Block to make things easier.
class IRBuilder {
    public:
        /// Create an IRBuilder with a Basic Block to insert instructions into
        /// @param block The Basic Block
        IRBuilder(BasicBlock* block);

        /// Update the underlying Basic Block to insert instructions into
        /// @param block The new basic block
        void SetBlock(BasicBlock* block);

        /// Create a Return Instruction
        /// @see RetInstruction::RetInstruction()
        /// @return The newly created Return Instruction
        Value* CreateRet(Value* value=nullptr);

    private:
        /// The Basic Block to insert newly created instructions into
        BasicBlock* _block = nullptr;
};

}}} // end namespace