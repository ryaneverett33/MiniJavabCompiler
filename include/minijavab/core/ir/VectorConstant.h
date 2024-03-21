#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>
#include <cassert>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/AggregateConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a vector constant containing n-number of elements
class VectorConstant : public AggregateConstant {
    public:
        /// Create a vector constant containing elements of the given type
        /// @param type The type of elements stored in this vector
        /// @param values The values stored in this vector
        VectorConstant(Type* type, std::initializer_list<Constant*> values);
        VectorConstant(Type* type, std::vector<Constant*> values);
        virtual void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace