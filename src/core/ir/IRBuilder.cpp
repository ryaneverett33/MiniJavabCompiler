#include "minijavab/core/ir/IRBuilder.h"

#include "minijavab/core/ir/Instructions/Ret.h"
#include "minijavab/core/ir/Instructions/Alloc.h"
#include "minijavab/core/ir/Instructions/Store.h"
#include "minijavab/core/ir/Instructions/Load.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IRBuilder::IRBuilder(BasicBlock* block)
    : Block(block) {}

Value* IRBuilder::CreateRet(Value* value) {
    Instruction* instruction = new RetInstruction();
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateAlloc(IR::Type* localType, std::string name) {
    Instruction* instruction = new AllocInstruction(localType, name);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateStore(Value* object, Value* pointer) {
    Instruction* instruction = new StoreInstruction(object, pointer);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateLoad(IR::Type* type, IR::Value* pointer) {
    Instruction* instruction = new LoadInstruction(type, pointer);
    Insert(instruction);

    return instruction;
}

void IRBuilder::Insert(Instruction* instruction) {
    Block->AppendInstruction(instruction);
}

}}} // end namespace