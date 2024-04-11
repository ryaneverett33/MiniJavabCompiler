#pragma once
#include <iostream>

namespace MiniJavab {
namespace Core {
namespace IR {
class Value;
class ValuePrinter;

class PrinterImpl {
    public:
        PrinterImpl(ValuePrinter* printer);
        ~PrinterImpl();

        void Print(std::ostream& out, const Value* value);
        void PrintNoType(std::ostream& out, const Value* value);
    private:
        ValuePrinter* _printer;
};

}}} // end namespace