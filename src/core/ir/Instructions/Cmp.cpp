#include "minijavab/core/ir/Instructions/Cmp.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

CmpInstruction::CmpInstruction(ComparisonOperation operation, Value* leftHandSide, Value* rightHandSide)
    : Instruction(Opcode::UNKNOWN, new IR::BooleanType()),
    _leftHandSide(leftHandSide),
    _rightHandSide(rightHandSide),
    _operation(operation) {
    
    _opcode = rightHandSide->IsImmediate() ? Opcode::CmpValueImmediate : Opcode::CmpValueValue;
}

bool CmpInstruction::YieldsValue() const {
    return true;
}

void CmpInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);
    out << " ";

    PrinterImpl printer = ValuePrinter::Get();
    switch (_operation) {
        case ComparisonOperation::Equal:
            out << "eq ";
            break;
        case ComparisonOperation::NotEqual:
            out << "ne ";
            break;
        case ComparisonOperation::GreaterThan:
            out << "gt ";
            break;
        case ComparisonOperation::GreaterThanEqualTo:
            out << "ge ";
            break;
        case ComparisonOperation::LessThan:
            out << "lt ";
            break;
        case ComparisonOperation::LessThanEqualTo:
            out << "le ";
            break;
        default:
            assert(false && "Unknown comparison operator");
    }
    printer.Print(out, _leftHandSide);
    out << ", ";
    printer.Print(out, _rightHandSide);
}

}}} // end namespace