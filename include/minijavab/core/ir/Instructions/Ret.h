#pragma once

#include "minijavab/core/ir/Instruction.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class RetInstruction : public Instruction {
    public:
        RetInstruction()
            : Instruction(Opcode::Ret, new IR::VoidType())
            {}

        bool YieldsValue() const override { return false; }
};

}}} // end namespace