#pragma once
#include <string>
#include <map>
#include <list>

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock;

class Function : public Value {
    public:
        Function(std::string name, FunctionType* type);

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        virtual void Print(std::ostream& out) const override;

        void AppendBasicBlock(BasicBlock* block);

        std::list<BasicBlock*> BasicBlocks;
        std::string Name;
};

}}} // end namespace