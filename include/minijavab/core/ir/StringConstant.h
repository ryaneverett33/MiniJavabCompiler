#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/VectorConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a constant whose value is a string
/// @todo: figure out vector population
class StringConstant : public VectorConstant {
    public:
        /// Creates a string constant with a given string
        /// @param value The underlying string
        StringConstant(std::string value);
        virtual void Print(std::ostream& out = std::cerr) const override;

        /// Get the string value of this constant
        /// @return The underlying string
        std::string GetString() const { return _stringValue; }
    private:
        /// The backing string
        std::string _stringValue;
};

}}} // end namespace