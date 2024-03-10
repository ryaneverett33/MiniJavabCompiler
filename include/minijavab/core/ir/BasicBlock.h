#pragma once
#include <string>
#include <list>

#include "minijavab/core/ir/Instruction.h"
#include "minijavab/core/ir/Function.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock : public Value {
    public:
        BasicBlock();
        BasicBlock(std::string name);

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

        void AppendInstruction(Instruction* instruction);

        std::list<BasicBlock*>::iterator Position;
        std::list<Instruction*> Instructions;

        /// The Function containing this Basic Block
        Function* ParentFunction = nullptr;
};

}}} // end namespace