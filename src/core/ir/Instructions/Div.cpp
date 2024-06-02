#include "minijavab/core/ir/Instructions/Div.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

DivInstruction::DivInstruction(Value* dividend, Value* divisor)
    : Instruction(Opcode::UNKNOWN, dividend->ValueType),
    _dividend(dividend),
    _divisor(divisor) {
    assert(dividend != nullptr && divisor != nullptr);
    
    _opcode = divisor->IsImmediate() ? Opcode::MulValueImmediate : Opcode::MulValueValue;
}

void DivInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " ";
    printer.Print(out, _dividend);
    out << ", ";
    printer.Print(out, _divisor);
}

}}} // end namespace