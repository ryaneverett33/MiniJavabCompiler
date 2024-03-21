#include "minijavab/core/ir/Function.h"

#include "minijavab/core/ir/BasicBlock.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Function::Function(std::string name, FunctionType* type)
    : Value(type),
    Name(name) {}

void Function::Print(std::ostream& out) const {
    FunctionType* functionType = static_cast<FunctionType*>(ValueType);

    out << functionType->ReturnType->GetString() << " " << Name << " (";
    for (size_t i = 0; i < functionType->ParameterTypes.size(); i++) {
        out << functionType->ParameterTypes[i]->GetString();

        if ((i + 1) < functionType->ParameterTypes.size()) {
            out << ", ";
        }
    }
    out << ")";

    if (BasicBlocks.empty()) {
        out << ";";
    }
    else {
        out << "\n";

        uint64_t temporaryCounter = 0;
        for (BasicBlock* block : BasicBlocks) {
            if (block->HasName()) { out << block->Name << ":\n"; }
            else { out << (temporaryCounter++) << ":\n"; }

            for (Instruction* inst : block->Instructions) {
                out << "\t";
                inst->Print(out);
                out << "\n";
            }
        }
    }
}

void Function::AppendBasicBlock(BasicBlock* block) {
    BasicBlocks.push_back(block);

    block->ParentFunction = this;
    block->Position = std::prev(BasicBlocks.end());
}

BasicBlock* Function::CreateBlock(std::string name) {
    BasicBlock* block = new BasicBlock(name);
    AppendBasicBlock(block);

    return block;
}

}}} // end namespace