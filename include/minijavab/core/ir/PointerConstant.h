#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Base class describing a constant that points to another constant
class PointerConstant : public Constant {
    public:
        /// Gets the pointed constant if one exists
        /// @return The pointed constant, else nullptr
        virtual Value* GetPointerTarget() const = 0;
    protected:
        /// Create a pointer constant for a given type
        /// @param type The type of the pointer
        PointerConstant(Type* type);
};

/// Describes a null pointer constant
class NullPointerConstant : public PointerConstant {
    public:
        /// Create a null pointer for a given type
        /// @param type The type of the pointer
        NullPointerConstant(Type* type);
        virtual Value* GetPointerTarget() const override;
        virtual void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace