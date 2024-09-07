#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {

/// Represents a bitcast instruction for typecasting a value of one type to another type
/// @example bitcast i8* %a to i32*
class BitcastInstruction : public Instruction {
    public:
        /// Construct a new bitcast instruction converting the value to a new type
        /// @param value The value to cast
        /// @param newType The new type that the value shall take
        BitcastInstruction(IR::Value* value, IR::Type* newType);

        bool YieldsValue() const override;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        /// The value that's being bitcasted
        IR::Value* _castee;
};

}}} // end namespace