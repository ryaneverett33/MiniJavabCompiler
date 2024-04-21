#pragma once
#include <iostream>

namespace MiniJavab {
namespace Core {
namespace IR {
class Value;
class ValuePrinter;

/// Implements a printer object for the ValuePrinter implementation
class PrinterImpl {
    public:
        /// Constructs a new PrinterImpl with a shared ValuePrinter instance
        /// @param printer The shared ValuePrinter instance, may not be null
        PrinterImpl(ValuePrinter* printer);
        ~PrinterImpl();

        /// Prints an IR::Value object to the output stream. Named IR::Value objects will be
        /// printed as their name, unnamed objects will be assigned a temporary ID that will be
        /// printed instead.
        /// @param out The output stream to print to
        /// @param value The value to print
        void Print(std::ostream& out, const Value* value);

        /// Similar to Print(), but prints IR::Value objects without any typing information 
        /// @param out The output stream to print to
        /// @param value The value to print
        void PrintNoType(std::ostream& out, const Value* value);
    private:
        /// The shared printer instance
        ValuePrinter* _printer;
};

}}} // end namespace