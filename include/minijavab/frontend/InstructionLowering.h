#pragma once
#include "minijavab/frontend/frontend.h"

#include <map>

namespace MiniJavab {
namespace Core {
namespace IR {
    class Function;
    class Value;
    class IRBuilder;
}} // end Core::IR namespace

namespace Frontend {
class ASTConverter;
class ASTMethod;

/// Responsible for lowering AST Function information to IR Functions
class InstructionLowering {
    /// Represents basic symbol information locally defined to a function
    struct FunctionSymbolEntry {
        /// The symbol value
        Core::IR::Value* Value = nullptr;
        
        /// Whether or not this symbol is a parameter.
        /// @see copiedSymbol
        bool isParameter = false;

        /// Points to the the copied parameter symbol if one exists.
        /// Parameter values are copied into local variables on function invocation.
        FunctionSymbolEntry* copiedSymbol = nullptr;
    };

    using FunctionSymbolTable = std::map<std::string, FunctionSymbolEntry*>;

    public:
        /// Construct an InstructionLowering object associated with a Converter object
        /// @param converter The Converter object constructing this object
        InstructionLowering(ASTConverter* converter);

        /// Lower a single function from AST to IR
        /// @param methodDefinition The AST definition of the function
        /// @param function The empty destination IR function
        void LowerFunction(ASTMethod* methodDefinition, Core::IR::Function* function);

        FunctionSymbolTable CreateLocalVariables(ASTMethod* methodDefinition, Core::IR::IRBuilder& builder);

    private:
        /// A reference to the main Converter object
        ASTConverter* _converter = nullptr;
};

}} // end namespace