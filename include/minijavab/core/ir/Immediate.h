#pragma once

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class Immediate: public Value {
    public:
        Immediate(IR::Type* type, uint64_t value);

        void Print(std::ostream& out) const override;

        // todo
        uint8_t GetU8() const;
        // todo
        uint32_t GetU32() const;
        // todo
        int8_t GetI8() const;
        // todo
        int32_t GetI32() const;
        // todo
        bool GetBoolean() const { return true; }
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

}}} // end namespace