#include "minijavab/core/ir/Instructions/Store.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

#include <cassert>

namespace MiniJavab {
namespace Core {
namespace IR {

StoreInstruction::StoreInstruction(Value* object, Value* pointer)
    : Instruction(Opcode::Store, new IR::VoidType()),
        _object(object),
        _pointer(pointer) {
    assert(pointer->ValueType->IsPointerType());

    IR::Type* elementType = static_cast<PointerType*>(pointer->ValueType)->ElementType;
    assert(object->ValueType->GetTypeKind() == elementType->GetTypeKind());
}

void StoreInstruction::Print(std::ostream& out) const {
    PrinterImpl printer = ValuePrinter::Get();
    Instruction::Print(out);

    out << " ";
    printer.Print(out, _object);
    out << ", ";
    printer.Print(out, _pointer);
}

}}} // end namespace