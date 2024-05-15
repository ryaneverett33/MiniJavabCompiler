#include "minijavab/core/ir/Instructions/Call.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/Function.h"

namespace MiniJavab {
namespace Core {
namespace IR {

CallInstruction::CallInstruction(IR::Function* function, std::vector<IR::Value*> arguments)
    : Instruction(Opcode::Call, nullptr),
    _calleeFunction(function) {
    FunctionType* functionType = static_cast<FunctionType*>(function->ValueType);

    // verify arguments are correct
    if (arguments.size() != functionType->ParameterTypes.size()) {
        throw std::invalid_argument("Invalid number of arguments!");
    }
    for (size_t i = 0; i < arguments.size(); i++) {
        if (arguments[i]->ValueType->GetTypeKind() != functionType->ParameterTypes[i]->GetTypeKind()) {
            throw std::invalid_argument("Argument types do not match");
        }
    }

    _arguments = arguments;
    ValueType = functionType->ReturnType;
}

bool CallInstruction::YieldsValue() const {
    return !ValueType->IsVoidType();
}

void CallInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);
    out << " ";

    PrinterImpl printer = ValuePrinter::Get();
    printer.Print(out, _calleeFunction);
    out << "(";
    for (size_t i = 0; i < _arguments.size(); i++) {
        printer.Print(out, _arguments[i]);

        if ((i + 1) < _arguments.size()) {
            out << ", ";
        }
    }

    out << ")";
}

}}} // end namespace