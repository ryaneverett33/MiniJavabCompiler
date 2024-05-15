#include "minijavab/core/ir/Instructions/GetPtr.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/GlobalVariable.h"

namespace MiniJavab {
namespace Core {
namespace IR {

GetPtrInstruction::GetPtrInstruction(IR::GlobalVariable* variable)
    : Instruction(Opcode::GetPtrValue, new PointerType(variable->ValueType)),
    _variable(variable) 
{}


GetPtrInstruction::GetPtrInstruction(IR::Type* type, uint32_t immediate)
    : Instruction(Opcode::GetPtrImmediate, nullptr),
    _immediate(immediate)
{
    ValueType = new PointerType(type);
}

bool GetPtrInstruction::ReferencesGlobalVariable() const {
    return _opcode == Opcode::GetPtrValue;
}

bool GetPtrInstruction::IsImmediatePointer() const {
    return _opcode == Opcode::GetPtrImmediate;
}

void GetPtrInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    if (IsImmediatePointer()) {
        PointerType* type = static_cast<PointerType*>(ValueType);
        out << type->ElementType->GetString() << static_cast<uint64_t>(_immediate);
    }
    else {
        out << " ";
        printer.Print(out, _variable);
    }
    //out << " " << ValueType->GetString() << ", ";
    //printer.Print(out, _pointer);
}

}}} // end namespace