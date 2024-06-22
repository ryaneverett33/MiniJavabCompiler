#include "minijavab/core/ir/GlobalVariable.h"

namespace MiniJavab {
namespace Core {
namespace IR {

GlobalVariable::GlobalVariable(std::string name, Constant* initializer)
                            : Value(initializer != nullptr ? initializer->ValueType : nullptr, name),
                            Initializer(initializer) {}

void GlobalVariable::Print(std::ostream& out) const {
    // EX: @var1 = 1 or @var1; if no initializer
    out << "@" << Name;
    if (Initializer != nullptr) {
        out << " = ";
        Initializer->Print(out);
    }
    else {
        out << ";";
    }
}

}}} // end namespace