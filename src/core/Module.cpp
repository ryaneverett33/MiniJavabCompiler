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

}

Function* Module::GetFunctionByName(std::string name) const {
    return nullptr;
}

void Module::AddGlobalVariable(GlobalVariable* variable) {

}

GlobalVariable* Module::GetGlobalVariableByName(std::string name) const {
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
}

}}} // end namespace