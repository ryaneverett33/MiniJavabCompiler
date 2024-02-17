#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/AggregateConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a structure constant value
class StructConstant : public AggregateConstant {
    public:
        /// Creates a structure constant for a given type
        /// @param type The structure type
        /// @param values The values within the structure
        StructConstant(Type* type, std::initializer_list<Constant*> values);
        virtual void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace