#include "minijavab/core/ir/Instruction.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Instruction::Instruction(Opcode opcode, IR::Type* type)
                : Value(type),
                _opcode(opcode) {}

void Instruction::Print(std::ostream& out) const {
    PrinterImpl printer = ValuePrinter::Get();
    if (YieldsValue()) {
        printer.PrintNoType(out, this);
        out << " = ";
    }
    out << GetInstructionName(_opcode);
}

}}} // end namespace