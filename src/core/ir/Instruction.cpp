#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Instruction::Instruction(Opcode opcode, IR::Type* type)
                : Value(type),
                _opcode(opcode) {}

void Instruction::Print(std::ostream& out) const {
    out << GetInstructionName(_opcode);
}

}}} // end namespace