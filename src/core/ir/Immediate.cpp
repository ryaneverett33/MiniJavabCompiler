#include "minijavab/core/ir/Immediate.h"

#include <cassert>

#include "minijavab/Casting.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Immediate::Immediate(IR::Type* type, uint64_t value)
    : Value(type),
    _value(value) {}

void Immediate::Print(std::ostream& out) const {
    if (ValueType->IsBooleanType()) {
        std::cout << std::boolalpha << GetBoolean();
    }
    else {
        IntegerType* intType = static_cast<IntegerType*>(ValueType);
        if (intType->IsSigned()) {
            std::cout << GetI32();
        }
        else {
            std::cout << GetU32();
        }
    }
}

uint8_t Immediate::GetU8() const {
    return cast::GetAsU8<uint64_t>(_value);
}

uint32_t Immediate::GetU32() const {
    return cast::GetAsU32<uint64_t>(_value);
}

int8_t Immediate::GetI8() const {
    return cast::GetAsI8<uint64_t>(_value);
}

int32_t Immediate::GetI32() const {
    return cast::GetAsI32<uint64_t>(_value);
}

bool Immediate::IsImmediate() const {
    return true;
}

}}} // end namespace