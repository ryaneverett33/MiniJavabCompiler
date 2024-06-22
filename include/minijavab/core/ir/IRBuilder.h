#pragma once

#include "minijavab/core/ir/BasicBlock.h"

#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {
class GlobalVariable;

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
        Value* CreateRet();

        /// Create a Return Instruction
        /// @see RetInstruction::RetInstruction(IR::Value*)
        /// @return The newly created Return Instruction
        Value* CreateRet(Value* value);

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

        /// Create a Getptr Instruction
        /// @see GetPtrInstruction::GetPtrInstruction()
        /// @return The newly created Getptr Instruction
        Value* CreateGetPtr(IR::GlobalVariable* variable);

        //Value* CreateGetPtr(IR::Type* type, uint32_t immediate);

        /// Create a Call Instruction
        /// @see CallInstruction::CallInstruction()
        /// @return The newly created Call Instruction
        Value* CreateCall(IR::Function* function, std::vector<IR::Value*> arguments);

        /// Create a Mul Instruction
        /// @see MulInstruction::MulInstruction()
        /// @return The newly created Mul Instruction
        Value* CreateMul(IR::Value* multiplicand, IR::Value* operand);

        /// Create an XOR Instruction
        /// @see XORInstruction::XORInstruction()
        /// @return The newly created XOR Instruction
        Value* CreateXOR(IR::Value* x, IR::Value* y);

        /// Create an Add Instruction
        /// @see AddInstruction::AddInstruction()
        /// @return The newly created Add Instruction
        Value* CreateAdd(IR::Value* augend, IR::Value* addend);

        /// Create a Sub Instruction
        /// @see SubInstruction::SubInstruction()
        /// @return The newly created Sub Instruction
        Value* CreateSub(IR::Value* minuend, IR::Value* subtrahend);

        /// Create a Div Instruction
        /// @see DivInstruction::DivInstruction()
        /// @return The newly created Div Instruction
        Value* CreateDiv(IR::Value* dividend, IR::Value* divisor);

        /// Wrapper function for inserting a created instruction into the block
        /// @see BasicBlock::AppendInstruction
        /// @param instruction The instruction to insert
        void Insert(Instruction* instruction);

        /// The Basic Block to insert newly created instructions into
        BasicBlock* Block = nullptr;
};

}}} // end namespace