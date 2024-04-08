#pragma once

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a function parameter that's passed into a function on invocation
class Parameter: public Value {
    public:
        /// Construct a parameter with a given type
        /// @param type The type of the parameter
        /// @param index The index of this parameter within the function's list of parameters
        Parameter(IR::Type* type, size_t index);

        /// Construct a parameter with a given type and name
        /// @param type The type of the parameter
        /// @param name The name of the parameter
        /// @param index The index of this parameter within the function's list of parameters
        Parameter(IR::Type* type, std::string name, size_t index);

        void Print(std::ostream& out = std::cerr) const override;

        /// Get the index of this parameter within the function's list of parameters
        /// @return The parameter index
        size_t GetIndex() const;

    private:
        /// The index of this parameter within the function's list of parameters
        size_t _index;
};

}}} // end namespace