#include "minijavab/core/ir/Instructions/Mul.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

MulInstruction::MulInstruction(Value* multiplicand, Value* multiplier)
    : Instruction(Opcode::UNKNOWN, multiplicand->ValueType),
    _multiplicand(multiplicand),
    _multiplier(multiplier) {
    assert(multiplicand != nullptr && multiplier != nullptr);
    
    _opcode = multiplier->IsImmediate() ? Opcode::MulValueImmediate : Opcode::MulValueValue;
}

void MulInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " ";
    printer.Print(out, _multiplicand);
    out << ", ";
    printer.Print(out, _multiplier);
}

}}} // end namespace