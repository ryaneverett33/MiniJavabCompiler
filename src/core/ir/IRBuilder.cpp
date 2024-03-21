#include "minijavab/core/ir/IRBuilder.h"

#include "minijavab/core/ir/Instructions/Ret.h"
#include "minijavab/core/ir/Instructions/Alloc.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IRBuilder::IRBuilder(BasicBlock* block)
    : _block(block) {}

void IRBuilder::SetBlock(BasicBlock* block) {
    _block = block;
}

Value* IRBuilder::CreateRet(Value* value) {
    Instruction* instruction = new RetInstruction();
    _block->AppendInstruction(instruction);

    return instruction;
}

Value* IRBuilder::CreateAlloc(IR::Type* localType, std::string name) {
    Instruction* instruction = new AllocInstruction(localType, name);
    _block->AppendInstruction(instruction);

    return instruction;
}

}}} // end namespace