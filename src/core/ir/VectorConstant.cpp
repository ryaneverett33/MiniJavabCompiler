#include "minijavab/core/ir/VectorConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

VectorConstant::VectorConstant(Type* type, std::initializer_list<Constant*> values)
    : AggregateConstant(type, values, ConstantKind::Vector) {
    assert(type->IsVectorType());

    // todo type check elements
}

VectorConstant::VectorConstant(Type* type, std::vector<Constant*> values)
    : AggregateConstant(type, values, ConstantKind::Vector) {
    assert(type->IsVectorType());

    // todo type check elements
}

void VectorConstant::Print(std::ostream& out) const {
    IR::VectorType* vectorType = static_cast<IR::VectorType*>(ValueType);
    
    out << "[" << _values.size() << " x " << vectorType->ElementType->GetString() << "]";
    AggregateConstant::Print(out);
}

}}} // end namespace