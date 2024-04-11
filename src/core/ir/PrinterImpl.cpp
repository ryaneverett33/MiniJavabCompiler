#include "minijavab/core/ir/PrinterImpl.h"

#include "minijavab/core/ir/ValuePrinter.h"
namespace MiniJavab {
namespace Core {
namespace IR {

PrinterImpl::PrinterImpl(ValuePrinter* printer)
    : _printer(printer) {}

PrinterImpl::~PrinterImpl() {
    _printer->implWasDestroyed();
}

void PrinterImpl::Print(std::ostream& out, const Value* value) {
    _printer->Print(out, value);
}

void PrinterImpl::PrintNoType(std::ostream& out, const Value* value) {
    _printer->PrintNoType(out, value);
}

}}} // end namespace