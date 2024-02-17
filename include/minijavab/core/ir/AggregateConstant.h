#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {
class Constant;

/// Base class for constant values that aggregate other constants within them
class AggregateConstant : public Constant {
    public:
        virtual void Print(std::ostream& out = std::cerr) const override;

        /// Get an element at a given index
        /// @param elementIndex The index to get the element from
        /// @return The element at the given index
        Constant* GetElement(size_t elementIndex);
    protected:
        /// @brief Create a new aggregate constant
        /// @param type The type of the constant
        /// @param values Values used for the initialization
        /// @param kind The kind of constant this is
        AggregateConstant(IR::Type* type, std::initializer_list<Constant*> values, ConstantKind kind);
        AggregateConstant(IR::Type* type, std::vector<Constant*> values, ConstantKind kind);

        /// The aggregate values stored in this constant
        std::vector<Constant*> _values;
};

}}} // end namespace