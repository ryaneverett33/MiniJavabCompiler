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

        void LowerStatement(AST::StatementNode* statement);
        void LowerStatement(AST::AssignmentStatementNode* statement);
        void LowerStatement(AST::IfStatementNode* statement);
        void LowerStatement(AST::NestedStatementsNode* statement);
        void LowerStatement(AST::PrintStatementNode* statement);
        void LowerStatement(AST::ReturnStatementNode* statement);
        void LowerStatement(AST::WhileStatementNode* statement);

        Core::IR::Value* LowerExpression(AST::ExpNode* expression);
        Core::IR::Value* LowerExpression(AST::LiteralExpNode* expression);
        Core::IR::Value* LowerExpression(AST::BinaryExpNode* expression);
        Core::IR::Value* LowerExpression(AST::ObjectExpNode* expression);

        /// Create any local variables needed for the function and save parameter values
        /// @param methodDefinition The AST definition of the function
        /// @return A symbol table for local variables/parameters used by this function
        FunctionSymbolTable CreateLocalVariables(ASTMethod* methodDefinition);

    private:
        /// A reference to the main Converter object
        ASTConverter* _converter = nullptr;

        /// A reference to current Instruction Builder object. Set by LowerFunction()
        Core::IR::IRBuilder* _builder = nullptr;

        /// A reference to the current function being lowered. Set By LowerFunction()
        Core::IR::Function* _function = nullptr;

        /// A reference to the current AST method definition that's being lowered
        ASTMethod* _methodDefinition = nullptr;

        /// A reference to the current symbol table for the function being lowered
        FunctionSymbolTable* _functionSymbolTable = nullptr;
};

}} // end namespace