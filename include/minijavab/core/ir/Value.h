#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Type.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Base class for objects that have a type and can be used by something else in the IR.
class Value {
    public:
        /// @todo get rid of this
        Value() {}
        Value(Type* type)
            : Type(type) {}

        /// Dump this object to the console
        virtual void Dump() const = 0;

        /// The type of this object
        Type* Type;
};

}}} // end namespace