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

bool Immediate::GetBoolean() const {
    return cast::GetAsBool<uint64_t>(_value);
}

bool Immediate::IsImmediate() const {
    return true;
}

void Immediate::Set(uint8_t value) {
    _value = cast::GetAsU64<uint8_t>(value);
}
void Immediate::Set(uint32_t value) {
    _value = cast::GetAsU64<uint32_t>(value);
}
void Immediate::Set(int8_t value) {
    _value = cast::GetAsU64<int8_t>(value);
}
void Immediate::Set(int32_t value) {
    _value = cast::GetAsU64<int32_t>(value);
}
void Immediate::Set(bool value) {
    _value = cast::GetAsU64<bool>(value);
}

}}} // end namespace