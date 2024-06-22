#include "minijavab/core/ir/Instructions/Add.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

AddInstruction::AddInstruction(Value* augend, Value* addend)
    : Instruction(Opcode::UNKNOWN, augend->ValueType),
    _augend(augend),
    _addend(addend) {
    assert(augend != nullptr && addend != nullptr);
    
    _opcode = addend->IsImmediate() ? Opcode::AddValueImmediate : Opcode::AddValueValue;
}

void AddInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " ";
    printer.Print(out, _augend);
    out << ", ";
    printer.Print(out, _addend);
}

}}} // end namespace