#include "minijavab/core/ir/Instructions/AND.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

ANDInstruction::ANDInstruction(Value* x, Value* y)
    : Instruction(Opcode::UNKNOWN, x->ValueType),
    _x(x),
    _y(y) {
    assert(x != nullptr && y != nullptr);
    
    _opcode = y->IsImmediate() ? Opcode::AndValueImmediate : Opcode::AddValueValue;
}

void ANDInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " ";
    printer.Print(out, _x);
    out << ", ";
    printer.Print(out, _y);
}

}}} // end namespace