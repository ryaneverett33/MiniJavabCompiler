#include "minijavab/core/ir/GlobalVariable.h"

namespace MiniJavab {
namespace Core {
namespace IR {
GlobalVariable::GlobalVariable(std::string name, Constant* value)
                            : Name(name),
                            Initializer(value) {}

void GlobalVariable::Dump() const {
    Print(std::cerr);
    std::cerr << "\n";
}
void GlobalVariable::Print(std::ostream& out) const {
    out << "@" << Name;
    if (Initializer != nullptr) {
        out << " = ";
        Initializer->Print(out);
    }
    else {
        out << ";";
    }
}

}}}