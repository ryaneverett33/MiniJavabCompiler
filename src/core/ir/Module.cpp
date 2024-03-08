#include "minijavab/core/ir/Module.h"

#include <iostream>

#include "minijavab/core/ir/Type.h"
#include "minijavab/core/ir/GlobalVariable.h"
#include "minijavab/core/ir/Function.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Module::Module(std::string name)
    : Name(name) {}

void Module::AddFunction(Function* function) {
    assert(GetFunctionByName(function->Name) == nullptr && "Function already registered!");

    _symbolTable.push_back(function);
    _functionCount += 1;
}

Function* Module::GetFunctionByName(std::string name) const {
    for (size_t i = _globalVariableCount; i < _functionCount; i++) {
        Function* function = static_cast<Function*>(_symbolTable[i]);
        if (function->Name == name) {
            return function;
        }
    }

    return nullptr;
}

void Module::AddGlobalVariable(GlobalVariable* variable) {
    assert(GetGlobalVariableByName(variable->Name) == nullptr && "variable already registered!");

    _symbolTable.insert(_symbolTable.begin() + _globalVariableCount, variable);
    _globalVariableCount += 1;
}

GlobalVariable* Module::GetGlobalVariableByName(std::string name) const {
    for (size_t i = 0; i < _globalVariableCount; i++) {
        GlobalVariable* variable = static_cast<GlobalVariable*>(_symbolTable[i]);
        if (variable->Name == name) {
            return variable;
        }
    }

    return nullptr;
}

void Module::AddStructType(MiniJavab::Core::IR::StructType* type) {
    assert(GetStructTypeByName(type->Name) == nullptr && "Struct already registered!");

    _structTypes.push_back(type);
}

MiniJavab::Core::IR::StructType* Module::GetStructTypeByName(std::string name) const {
    for (MiniJavab::Core::IR::StructType* type : _structTypes) {
        if (type->Name == name) { return type; }
    }
    return nullptr;
}

void Module::Dump() {
    if (GetNumberOfGlobalVariables() && 
        GetNumberOfFunctions() == 0 &&
        _structTypes.empty()) {
        std::cerr << "Module is empty!\n";
        return;
    }

    // Dump naming info
    std::cout << "; module";
    if (!Name.empty()) {
        std::cout << " \"" << Name << "\"";
    }
    std::cout << "\n";
    
    // Dump custom types
    if (!_structTypes.empty()) {
        std::cout << "; Types\n";
        for (StructType* type : _structTypes) {
            type->Dump();
        }
    }

    if (GetNumberOfGlobalVariables() > 0) {
        std::cout << "; Global Variables\n";
        for (Value* value : GetGlobalVariables()) {
            static_cast<GlobalVariable*>(value)->Dump();
        }
    }

    if (GetNumberOfFunctions() > 0) {
        std::cout << "; Functions\n";
        for (Value* value : GetFunctions()) {
            static_cast<Function*>(value)->Dump();
        }
    }
}

}}} // end namespace