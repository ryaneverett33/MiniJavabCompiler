#include "minijavab/frontend/InstructionLowering.h"

#include "minijavab/frontend/Converter.h"
#include "minijavab/frontend/ASTClassTable.h"

#include "minijavab/core/ir/Function.h"
#include "minijavab/core/ir/BasicBlock.h"
#include "minijavab/core/ir/IRBuilder.h"

using namespace MiniJavab::Core;

namespace MiniJavab {
namespace Frontend {

InstructionLowering::InstructionLowering(ASTConverter* converter)
                        : _converter(converter) {}

void InstructionLowering::LowerFunction(ASTMethod* methodDefinition, Core::IR::Function* function) {
    // Create Function Symbol Table

    // Create entry block
    IR::BasicBlock* entryBlock = function->CreateBlock("entry");

    IR::IRBuilder builder(entryBlock);
    builder.CreateRet();
}


}} // end namespace