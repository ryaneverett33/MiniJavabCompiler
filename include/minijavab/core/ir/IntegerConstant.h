#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"
#include "minijavab/core/ir/Immediate.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a constant integer value
class IntegerConstant : public Constant {
    public:
        /// Create a new integer constant
        /// @param type The integer type
        /// @param value The value (will be casted accordingly)
        IntegerConstant(IR::Type* type, Immediate* value);

        virtual void Print(std::ostream& out) const override;

        /// The constant value
        Immediate* Value;
};

/// Describes a constant boolean value
class BooleanConstant : public IntegerConstant {
    public:
        /// Create a new boolean constant
        /// @param value The boolean value
        BooleanConstant(bool value);

        void Print(std::ostream& out) const override;
};

}}} // end namespace