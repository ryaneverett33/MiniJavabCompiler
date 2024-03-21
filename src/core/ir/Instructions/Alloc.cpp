#include "minijavab/core/ir/Instructions/Alloc.h"

namespace MiniJavab {
namespace Core {
namespace IR {

AllocInstruction::AllocInstruction(IR::Type* localType, std::string name)
    : Instruction(Opcode::Alloc, localType) {
    Name = name;
}

void AllocInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    out << " " << ValueType->GetString();
}

}}} // end namespace