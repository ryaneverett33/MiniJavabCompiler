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
        /// Construct a value with a given type
        /// @param type The type of the value
        Value(IR::Type* type)
            : ValueType(type) {}

        /// Print the textual representation of this constant to stderr
        /// @see Value::Print()
        void Dump() const;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        virtual void Print(std::ostream& out = std::cerr) const = 0;

        /// The type of this object
        IR::Type* ValueType;
};

}}} // end namespace