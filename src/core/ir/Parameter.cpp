#include "minijavab/core/ir/Parameter.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

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
    PrinterImpl printer = ValuePrinter::Get();
    printer.Print(out, this);
}

}}} // end namespace