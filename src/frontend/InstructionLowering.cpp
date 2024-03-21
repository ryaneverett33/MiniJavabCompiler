#include "minijavab/frontend/InstructionLowering.h"

#include "minijavab/frontend/Converter.h"
#include "minijavab/frontend/ASTClassTable.h"

#include "minijavab/core/ir/Function.h"
#include "minijavab/core/ir/BasicBlock.h"
#include "minijavab/core/ir/IRBuilder.h"

using namespace MiniJavab::Core;

namespace MiniJavab {
namespace Frontend {

InstructionLowering::InstructionLowering(ASTConverter* converter)
                        : _converter(converter) {}

InstructionLowering::FunctionSymbolTable InstructionLowering::CreateLocalVariables(ASTMethod* methodDefinition, Core::IR::IRBuilder& builder) {
    FunctionSymbolTable functionSymbolTable;

    // Create local variables for each passed-in parameter
    for (auto& [parameterName, parameter] : methodDefinition->Parameters) {
        // Create a new local variable as a copy of the passed-in parameter
        IR::Value* localVariable = builder.CreateAlloc(_converter->ResolveASTType(parameter->Type),
                                                            parameterName + ".local");

        // Create two symbol table entries, one for the passed-in parameter and one for the copy
        FunctionSymbolEntry* localEntry = new FunctionSymbolEntry {
            /*Value*/ localVariable,
            /*isParameter*/ false,
            /*copiedSymbol*/ nullptr
        };

        FunctionSymbolEntry* parameterEntry = new FunctionSymbolEntry {
            /*Value*/ nullptr,  // TODO: Get the parameter as a value somehow
            /*isParameter*/ true,
            /*copiedSymbol*/ localEntry
        };

        functionSymbolTable.insert({localVariable->Name, localEntry});
        functionSymbolTable.insert({parameterName, parameterEntry});
    }

    // Create local variables for each variable declaration in the method
    for (auto& [variableName, variable] : methodDefinition->Variables) {
        IR::Value* localVariable = builder.CreateAlloc(_converter->ResolveASTType(variable->Type),
                                                            variableName);

        functionSymbolTable.insert({variableName, new FunctionSymbolEntry {
            /*Value*/ localVariable,
            /*isParameter*/ false,
            /*copiedSymbol*/ nullptr
        }});
    }

    return functionSymbolTable;
}

void InstructionLowering::LowerFunction(ASTMethod* methodDefinition, Core::IR::Function* function) {
    // Create entry block and an IR Builder to use it
    IR::BasicBlock* entryBlock = function->CreateBlock("entry");
    IR::IRBuilder builder(entryBlock);

    // Convert any function parameters to local variables
    FunctionSymbolTable functionSymbolTable = CreateLocalVariables(methodDefinition, builder);

    builder.CreateRet();
}


}} // end namespace