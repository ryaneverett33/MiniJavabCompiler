#include "minijavab/core/ir/Instructions/Bitcast.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/BasicBlock.h"

namespace MiniJavab {
namespace Core {
namespace IR {

BitcastInstruction::BitcastInstruction(IR::Value* value, IR::Type* newType)
    : Instruction(Opcode::Bitcast, newType),
    _castee(value) {
    if (!value->ValueType->IsPointerType()) {
        throw std::invalid_argument("Value must be a pointer type");
    }
    if (!newType->IsPointerType()) {
        throw std::invalid_argument("Casted type be a pointer type");
    }
}

bool BitcastInstruction::YieldsValue() const {
    return true;
}

void BitcastInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);
    out << " ";

    PrinterImpl printer = ValuePrinter::Get();
    printer.Print(out, _castee);
    out << " to " << ValueType->GetString();
}

}}} // end namespace