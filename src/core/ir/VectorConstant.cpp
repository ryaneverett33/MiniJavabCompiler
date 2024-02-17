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
    IR::VectorType* structType = static_cast<IR::VectorType*>(ValueType);
    
    out << "[ ";
    for (size_t i = 0; i < _values.size(); i++) {
        _values[i]->Print(out);
        if ((i + 1) < _values.size()) {
            out << ", ";
        }
    }
    out << " ]";
}

}}} // end namespace