#include "minijavab/core/ir/Instructions/Load.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

LoadInstruction::LoadInstruction(IR::Type* type, IR::Value* pointer)
    : Instruction(Opcode::Load, nullptr),
    _pointer(pointer) {
    assert(pointer->ValueType->IsPointerType());
    
    PointerType* pointerType = static_cast<PointerType*>(pointer->ValueType);
    assert(type->GetTypeKind() == pointerType->ElementType->GetTypeKind());

    ValueType = pointerType->ElementType;
}

void LoadInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);

    PrinterImpl printer = ValuePrinter::Get();
    out << " " << ValueType->GetString() << ", ";
    printer.Print(out, _pointer);
}

}}} // end namespace