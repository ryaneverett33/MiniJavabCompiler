#include "minijavab/core/ir/Instructions/OR.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

ORInstruction::ORInstruction(Value* x, Value* y)
    : Instruction(Opcode::UNKNOWN, x->ValueType),
    _x(x),
    _y(y) {
    assert(x != nullptr && y != nullptr);
    
    _opcode = y->IsImmediate() ? Opcode::OrValueImmediate : Opcode::OrValueValue;
}

void ORInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " ";
    printer.Print(out, _x);
    out << ", ";
    printer.Print(out, _y);
}

}}} // end namespace