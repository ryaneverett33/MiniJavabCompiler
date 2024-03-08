#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes a runtime constant Global Variable with a given initializer 
class GlobalVariable : public Value {
    public:
        /// Creates a new Global Variable object.
        /// @note Caller is responsible for adding this object to the module
        /// @param name The unique name for the variable
        /// @param initializer The constant to initialize this variable with.
        GlobalVariable(std::string name, Constant* initializer);

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        void Print(std::ostream& out = std::cerr) const;

        /// The unique name of this variable
        std::string Name;

        /// The constant value to initialize this variable with
        Constant* Initializer;
};

}}} // end namespace