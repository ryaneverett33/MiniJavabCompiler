#pragma once

#include "minijavab/core/ir/Instruction.h"

#include <string>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {

/// The comparison operation to perform
enum class ComparisonOperation {
    Equal,
    NotEqual,
    LessThan,
    LessThanEqualTo,
    GreaterThan,
    GreaterThanEqualTo
};

/// Represents a comparison operation between two different values
class CmpInstruction : public Instruction {
    public:
        /// Create a br instruction to the target basic block
        /// @param target The control flow block to branch to

        /// Create a cmp instruction against two values with a given comparison
        /// @param operation The comparison to perform
        /// @param leftHandSide The left hand side of the operation
        /// @param rightHandSide The right hand side of the operation
        CmpInstruction(ComparisonOperation operation, Value* leftHandSide, Value* rightHandSide);

        bool YieldsValue() const override;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const override;

    private:
        /// The type of the comparison to perform
        ComparisonOperation _operator;
        /// The left hand side of the comparison
        Value* _leftHandSide;
        /// The right hand side of the comparison
        Value* _rightHandSide;
};

}}} // end namespace