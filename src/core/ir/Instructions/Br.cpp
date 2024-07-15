#include "minijavab/core/ir/Instructions/Br.h"

#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/BasicBlock.h"

namespace MiniJavab {
namespace Core {
namespace IR {

BrInstruction::BrInstruction(IR::BasicBlock* target)
    : Instruction(Opcode::Br, new IR::VoidType()),
    _targetBlock(target) {}

bool BrInstruction::YieldsValue() const {
    return false;
}

void BrInstruction::Print(std::ostream& out) const {
    Instruction::Print(out);
    out << " ";

    PrinterImpl printer = ValuePrinter::Get();
    printer.Print(out, _targetBlock);
}

}}} // end namespace