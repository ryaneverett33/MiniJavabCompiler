#include "minijavab/core/ir/BasicBlock.h"

namespace MiniJavab {
namespace Core {
namespace IR {

BasicBlock::BasicBlock()
    : Value(new IR::VoidType()) {}

BasicBlock::BasicBlock(std::string name)
    : Value(new IR::VoidType(), name) {}

void BasicBlock::Print(std::ostream& out) const {

}

void BasicBlock::AppendInstruction(Instruction* instruction) {
    Instructions.push_back(instruction);

    instruction->ParentBlock = this;
    instruction->Position = std::prev(Instructions.end());
}

}}} // end namespace