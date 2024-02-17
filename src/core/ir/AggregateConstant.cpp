#include "minijavab/core/ir/AggregateConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

AggregateConstant::AggregateConstant(Type* type, std::initializer_list<Constant*> values, ConstantKind kind)
    : Constant(type, kind),
    _values(values) {}
AggregateConstant::AggregateConstant(Type* type, std::vector<Constant*> values, ConstantKind kind)
    : Constant(type, kind),
    _values(values) {}

Constant* AggregateConstant::GetElement(size_t elementIndex) {
    return _values.at(elementIndex);
}

}}} // end namespace