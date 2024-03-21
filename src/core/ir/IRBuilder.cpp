#include "minijavab/core/ir/IRBuilder.h"

#include "minijavab/core/ir/Instructions/Ret.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IRBuilder::IRBuilder(BasicBlock* block)
    : _block(block) {}

void IRBuilder::SetBlock(BasicBlock* block) {
    _block = block;
}

Value* IRBuilder::CreateRet(Value* value) {
    Instruction* retInstruction = new RetInstruction();
    _block->AppendInstruction(retInstruction);

    return retInstruction;
} 

}}} // end namespace