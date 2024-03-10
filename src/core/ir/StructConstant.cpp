#include "minijavab/core/ir/StructConstant.h"

#include <cassert>

namespace MiniJavab {
namespace Core {
namespace IR {

StructConstant::StructConstant(Type* type, std::initializer_list<Constant*> values)
    : AggregateConstant(type, values, ConstantKind::Struct) {
    assert(type->IsStructType());

    // todo type check elements
}

void StructConstant::Print(std::ostream& out) const {
    IR::StructType* structType = static_cast<IR::StructType*>(ValueType);
    
    out << structType->GetString();
    AggregateConstant::Print(out);
}

}}} // end namespace