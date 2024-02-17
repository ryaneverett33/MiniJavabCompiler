#include "minijavab/core/ir/StructConstant.h"

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
    
    out << structType->GetString() << " { ";
    for (size_t i = 0; i < _values.size(); i++) {
        _values[i]->Print(out);
        if ((i + 1) < _values.size()) {
            out << ", ";
        }
    }
    out << " }";
}

}}} // end namespace