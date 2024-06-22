#include "minijavab/core/ir/IntrinsicFunction.h"

#include "minijavab/core/ir/BasicBlock.h"
#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IntrinsicFunction::IntrinsicFunction(std::string name, FunctionType* type)
    : Function(name, type)
{}

void IntrinsicFunction::AppendBasicBlock(BasicBlock* block) {
    assert(false && "Cannot append basic blocks to an intrinsic function");
}

BasicBlock* IntrinsicFunction::CreateBlock(std::string name) {
    assert(false && "Cannot create basic blocks for an intrinsic function");
}

std::list<BasicBlock*>* IntrinsicFunction::GetBlocks() {
    assert(false && "Intrinsic Functions do not have any basic blocks attached to them");
}

bool IntrinsicFunction::IsDefined() const {
    return false;
}

}}} // end namespace