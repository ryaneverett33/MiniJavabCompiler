#pragma once
#include <string>
#include <map>
#include <vector>
#include <utility>

#include "minijavab/iterator_range.h"

#include "minijavab/core/ir/GlobalVariable.h"
#include "minijavab/core/ir/Function.h"
#include "minijavab/core/ir/IntrinsicFunction.h"

namespace MiniJavab {
namespace Core {
namespace IR {
class Type;
class StructType;
class Value;

const std::string MJ_PRINTLN_STR_INTRINSIC = "mj.println.str";
const std::string MJ_PRINTLN_INT_INTRINSIC = "mj.println.int";
const std::string MJ_NEW_INTRINSIC = "mj.new";
const std::string MJ_DELETE_INTRINSIC = "mj.delete";

/// Describes a single module in the IR. A module is a single linkable object that contains
/// functions, global variables, and unique types. A module may encompass multiple Compile Units. 
class Module {
    public:
        /// Create a new unnamed module
        Module() {}

        /// Create a new module with a given name
        /// @param name The name of the new module
        Module(std::string name);

        /// Get all Functions in the Module
        /// @return An iterable list of functions
        llvm::iterator_range<std::vector<Value*>::iterator> GetFunctions() {
            if (_functionCount == 0) {
                return llvm::make_range(_symbolTable.end(), _symbolTable.end());
            }
            return llvm::make_range(_symbolTable.begin() + _globalVariableCount, _symbolTable.end());
        }

        /// Get all Global Variables in the Module
        /// @return An iterable list of Global Variables
        llvm::iterator_range<std::vector<Value*>::iterator> GetGlobalVariables() {
            if (_globalVariableCount == 0) {
                return llvm::make_range(_symbolTable.end(), _symbolTable.end());
            }
            return llvm::make_range(_symbolTable.begin(), _symbolTable.end() - _functionCount);
        }

        /// Add a new Function to the Module
        /// @todo what happens if the function name already exists?
        /// @param function Function to add 
        void AddFunction(Function* function);

        /// Lookup a Function by name
        /// @param name The name of the Function to lookup
        /// @return The Function, if it exists, else nullptr
        Function* GetFunctionByName(std::string name) const;

        /// Lookup an intrinsic function. If the intrinsic doesn't exist, an exception will be thrown
        /// @return The intrinsic function
        IntrinsicFunction* GetIntrinsic(std::string name);

        /// Lookup a typed intrinsic function. A type intrinsic function is a unique stub-based intrinsic
        /// that uses typing information. If the intrinsic doesn't exist, an exception will be thrown
        /// @param name The intrinsic function
        /// @param type The type info associated with the intrinsic
        /// @return The intrinsic function
        IntrinsicFunction* GetTypedIntrinsic(std::string name, Type* type);

        /// Get the number of Functions in the Module
        /// @return The number of Functions in the Module
        size_t GetNumberOfFunctions() const { return _functionCount; }

        /// Add a new Global Variable to the Module
        /// @todo what happens if the Global Variable name already exists?
        /// @param variable Global Variable to add
        void AddGlobalVariable(GlobalVariable* variable);

        /// Add a new anonymous string value to the Module and return it for use
        /// @param value The string to initialize the constant with
        /// @return The new String Constant Global Variable
        GlobalVariable* AddStringConstant(std::string value);

        /// Lookup a Global Variable by its name
        /// @param name The name of the Global Variable to lookup
        /// @return The Global Variable, if it exists, else nullptr
        GlobalVariable* GetGlobalVariableByName(std::string name) const;

        /// Get the number of Global Variables in the Module
        /// @return The number of Global Variables in the Module
        size_t GetNumberOfGlobalVariables() const { return _globalVariableCount; }

        /// Register a new struct type within the module
        /// @param type The struct type to register
        void AddStructType(Core::IR::StructType* type);

        /// Lookup a Struct Type by its name
        /// @param name The name of the Struct Type to lookup
        /// @return The Struct Type, if it exists, else nullptr
        StructType* GetStructTypeByName(std::string name) const;

        /// Dump the module definition, in text format, to stdout
        void Dump();

        /// The name of the Module, if one has been given
        std::string Name;
    private:
        /// Helper function for inserting functions into the symbol table. Callers must verify
        /// that the function can be inserted before calling
        /// @param function Function to add
        void addFunctionHelper(Function* function);

        /// A list of all Global Variables and Functions in the Module.
        /// Ordered by Global Variables, then Functions.
        std::vector<Value*> _symbolTable;

        /// A list of all Struct Types in the Module
        std::vector<StructType*> _structTypes;

        /// The number of Global Variables in the Module
        size_t _globalVariableCount = 0;

        /// The number of Functions in the Module
        size_t _functionCount = 0;

        /// The number of anonymous string constants in this module
        size_t _stringConstantCount = 0;
};

}}} // end namespace