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

        /// Construct a value with a given type and name
        /// @param type The type of the value
        /// @param name The name of the value
        Value(IR::Type* type, std::string name)
            : ValueType(type),
            Name(name) {}

        /// Print the textual representation of this constant to stderr
        /// @see Value::Print()
        void Dump() const {
            Print(std::cerr);
            std::cerr << "\n";
        }
        
        bool HasName() const { return !Name.empty(); }

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        virtual void Print(std::ostream& out = std::cerr) const = 0;

        /// Whether or not this value is an immediate value
        /// @see IR::Immediate
        /// @return True if it's an immediate value, false otherwise
        virtual bool IsImmediate() const { return false; }

        /// The type of this object
        IR::Type* ValueType = nullptr;

        /// The optional name associated with this value
        std::string Name;
};

}}} // end namespace