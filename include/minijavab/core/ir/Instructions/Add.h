#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class AddInstruction : public Instruction {
    public:
        AddInstruction(Value* arg1, Value* arg2);
};

}}} // end namespace