#pragma once
#include <string>
#include <map>
#include <vector>
#include <iostream>

#include "minijavab/core/ir/Type.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Base class for objects that have a type and can be used by something else in the IR.
class Value {
    public:
        /// @todo get rid of this
        Value() {}
        Value(IR::Type* type)
            : ValueType(type) {}

        /// Dump this object to the console
        void Dump() const;
        virtual void Print(std::ostream& out = std::cerr) const = 0;

        /// The type of this object
        IR::Type* ValueType;
};

}}} // end namespace