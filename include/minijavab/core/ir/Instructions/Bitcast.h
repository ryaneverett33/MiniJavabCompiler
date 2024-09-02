#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {

/// @todo
class BitcastInstruction : public Instruction {
    public:
        /// @todo
        BitcastInstruction(IR::Value* value, IR::Type* newType);

        bool YieldsValue() const override;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        IR::Value* _castee;
};

}}} // end namespace