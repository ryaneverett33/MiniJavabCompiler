#include "minijavab/core/ir/Instructions/BrIf.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/BasicBlock.h"

namespace MiniJavab {
namespace Core {
namespace IR {

BrIfInstruction::BrIfInstruction(IR::BasicBlock* target, IR::Value* conditional)
    : Instruction(Opcode::BrIf, new IR::VoidType()),
    _targetBlock(target),
    _conditional(conditional) {}

bool BrIfInstruction::YieldsValue() const {
    return false;
}

void BrIfInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);
    out << " ";

    PrinterImpl printer = ValuePrinter::Get();
    printer.PrintNoType(out, _targetBlock);
    out << ", ";
    printer.Print(out, _conditional);
}

}}} // end namespace