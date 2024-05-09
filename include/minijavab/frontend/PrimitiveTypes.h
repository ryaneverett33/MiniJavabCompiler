#pragma once
#include "minijavab/core/ir/Type.h"

namespace MiniJavab {
namespace Frontend {

/// Helper methods for quickly translating MiniJavab types to IR types
namespace PrimitiveTypes {

/// Creates an IR type representing an `int` type
/// @return The new IR type
inline Core::IR::IntegerType* Int() {
    return new Core::IR::IntegerType(32);
}

/// Creates an IR type representing a `boolean` type
/// @return The new IR type
inline Core::IR::BooleanType* Boolean() {
    return new Core::IR::BooleanType();
}

}}} // end namespace