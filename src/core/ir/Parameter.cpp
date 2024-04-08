#include "minijavab/core/ir/Parameter.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Parameter::Parameter(IR::Type* type, size_t index)
        : Value(type),
        _index(index) {}

Parameter::Parameter(IR::Type* type, std::string name, size_t index)
            : Value(type, name),
            _index(index) {}

size_t Parameter::GetIndex() const {
    return _index;
}

void Parameter::Print(std::ostream& out) const {
    out << ValueType->GetString() << " %" << (HasName() ? Name : (std::to_string(_index)));
}

}}} // end namespace