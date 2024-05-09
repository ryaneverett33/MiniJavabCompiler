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

        /// Create a Return Instruction
        /// @see RetInstruction::RetInstruction()
        /// @return The newly created Return Instruction
        Value* CreateRet(Value* value=nullptr);

        /// Create a Allocation Instruction
        /// @see AllocInstruction::AllocInstruction()
        /// @return The newly created Allocation Instruction
        Value* CreateAlloc(IR::Type* localType, std::string name);

        /// Create a Store Instruction
        /// @see StoreInstruction::StoreInstruction()
        /// @return The newly created Store Instruction
        Value* CreateStore(Value* object, Value* pointer);

        /// Create a Load Instruction
        /// @see LoadInstruction::LoadInstruction()
        /// @return The newly created Load Instruction
        Value* CreateLoad(IR::Type* type, IR::Value* pointer);

        /// Wrapper function for inserting a created instruction into the block
        /// @see BasicBlock::AppendInstruction
        /// @param instruction The instruction to insert
        void Insert(Instruction* instruction);

        /// The Basic Block to insert newly created instructions into
        BasicBlock* Block = nullptr;
};

}}} // end namespace