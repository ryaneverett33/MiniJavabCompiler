#include "minijavab/core/ir/IntegerConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IntegerConstant::IntegerConstant(IR::Type* type, uint64_t value)
    : Constant(type, ConstantKind::Integer),
    _value(value) {
    //assert(type->IsIntegerType());
    
    // todo do bit width checking
}

void IntegerConstant::Print(std::ostream& out) const {
    IR::IntegerType* intType = static_cast<IR::IntegerType*>(ValueType);

    if (intType->IsSigned()) {
        std::cout << std::dec << static_cast<int64_t>(_value);
    }
    else {
        std::cout << std::dec << static_cast<uint64_t>(_value);
    }
}

BooleanConstant::BooleanConstant(bool value)
    : IntegerConstant(new IR::BooleanType(), static_cast<uint64_t>(value))
    {}

void BooleanConstant::Print(std::ostream& out) const {
    out << std::boolalpha << GetValue();
}

bool BooleanConstant::GetValue() const {
    return static_cast<bool>(_value);
}

}}} // end namespace