#include "minijavab/core/ir/Function.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Function::Function(std::string name, FunctionType* type)
    : Value(type),
    Name(name) {}

void Function::Print(std::ostream& out) const {
    FunctionType* functionType = static_cast<FunctionType*>(ValueType);

    out << functionType->ReturnType->GetString() << " " << Name << " (";
    for (size_t i = 0; i < functionType->ParameterTypes.size(); i++) {
        out << functionType->ParameterTypes[i]->GetString();

        if ((i + 1) < functionType->ParameterTypes.size()) {
            out << ", ";
        }
    }
    out << ")";
}

}}} // end namespace