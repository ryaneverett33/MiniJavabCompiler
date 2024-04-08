#pragma once
#include <string>
#include <map>
#include <list>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Parameter.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock;

/// Represents a locally defined function within the IR. A function contains a list of
/// Basic Blocks that define the instructions. 
class Function : public Value {
    public:
        /// Create an empty Function with a given name and type
        /// @param name Name of the function
        /// @param type Type of the function
        Function(std::string name, FunctionType* type);

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        virtual void Print(std::ostream& out) const override;

        /// @todo is this needed?
        void AppendBasicBlock(BasicBlock* block);

        /// Helper function for creating a new Basic Block and appending it to the function
        /// @param name Name of the basic block to create
        /// @return The newly created, and inserted, basic block
        BasicBlock* CreateBlock(std::string name);

        /// Get the list of parameters used by this function
        /// @return A copy of the list of function parameters
        std::vector<Parameter*> GetParameters() const;

        /// Lookup a function parameter by known name
        /// @see GetParameters()
        /// @return The parameter if it exists, else nullptr
        Parameter* GetParameterByName(std::string name) const;

        /// Lookup a function parameter by known index
        /// @see GetParameters()
        /// @return the Parameter if it exists, else nullptr
        Parameter* GetParameterByIndex(size_t index) const;

        /// The list of Basic Blocks in this function
        std::list<BasicBlock*> BasicBlocks;

        /// The name of this function
        std::string Name;
    private:
        /// List of parameters passed to this function
        std::vector<Parameter*> _parameterList;
};

}}} // end namespace