#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a constant integer value
class IntegerConstant : public Constant {
    public:
        /// Create a new integer constant
        /// @param type The integer type
        /// @param value The value (will be casted accordingly)
        IntegerConstant(IR::Type* type, uint64_t value);

        virtual void Print(std::ostream& out) const;
        
        // todo
        uint8_t GetU8() const;
        // todo
        uint32_t GetU32() const;
        // todo
        int8_t GetI8() const;
        // todo
        int32_t GetI32() const;
        // todo
        void Set(uint8_t value);
        // todo
        void Set(uint32_t value);
        // todo
        void Set(int8_t value);
        // todo
        void Set(int32_t value);
    protected:
        /// The raw uncasted integer value
        uint64_t _value;
};

/// Describes a constant boolean value
class BooleanConstant : public IntegerConstant {
    public:
        /// Create a new boolean constant
        /// @param value The boolean value
        BooleanConstant(bool value);

        virtual void Print(std::ostream& out) const;

        /// Get the value of the constant
        /// @return The underlying value
        bool GetValue() const;
};

}}} // end namespace