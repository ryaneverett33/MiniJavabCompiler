#include "minijavab/core/ir/Instructions/Ret.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

RetInstruction::RetInstruction()
    : Instruction(Opcode::Ret, new IR::VoidType())
    {}

RetInstruction::RetInstruction(IR::Value* returnValue)
    : Instruction(Opcode::RetImmediate, nullptr),
    _returnValue(returnValue) {
    assert(returnValue != nullptr);

    ValueType = returnValue->ValueType;
}

void RetInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    if (_opcode == Opcode::RetImmediate) {
        PrinterImpl printer = ValuePrinter::Get();
        out << " ";
        printer.Print(out, _returnValue);
    }
}

}}} // end namespace