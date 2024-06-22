#include "minijavab/core/ir/Instructions/Sub.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

SubInstruction::SubInstruction(Value* minuend, Value* subtrahend)
    : Instruction(Opcode::UNKNOWN, subtrahend->ValueType),
    _minuend(minuend),
    _subtrahend(subtrahend) {
    assert(minuend != nullptr && subtrahend != nullptr);
    
    _opcode = subtrahend->IsImmediate() ? Opcode::SubValueImmediate : Opcode::SubValueValue;
}

void SubInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " ";
    printer.Print(out, _minuend);
    out << ", ";
    printer.Print(out, _subtrahend);
}

}}} // end namespace