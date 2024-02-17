#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class IntegerConstant : public Constant {
    public:
        IntegerConstant(IR::Type* type, uint64_t value);

        virtual void Print(std::ostream& out) const;
        uint8_t GetU8() const;
        uint32_t GetU32() const;
        int8_t GetI8() const;
        int32_t GetI32() const;
        void Set(uint8_t value);
        void Set(uint32_t value);
        void Set(int8_t value);
        void Set(int32_t value);
    private:
        uint64_t _value;
};

}}} // end namespace