#include "minijavab/core/ir/Immediate.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Immediate::Immediate(IR::Type* type, uint64_t value)
    : Value(type),
    _value(value) {}

void Immediate::Print(std::ostream& out) const
{
    std::cout << _value;
}

}}} // end namespace