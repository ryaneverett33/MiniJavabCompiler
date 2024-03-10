#pragma once
#include <string>
#include <list>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Instructions/Opcodes.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock;

class Instruction : public Value {
    public:
        Instruction(Opcode opcode, IR::Type* type);

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const;

        // Whether or not this instruction returns a value for immediate usage
        virtual bool YieldsValue() const = 0;

        std::list<Instruction*>::iterator Position;
        BasicBlock* ParentBlock = nullptr;

    protected:
        Opcode _opcode;
};

}}} // end namespace