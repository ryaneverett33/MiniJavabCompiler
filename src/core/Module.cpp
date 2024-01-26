#include "minijavab/core/ir/Module.h"

#include <iostream>

#include "minijavab/core/ir/Type.h"
#include "minijavab/core/ir/GlobalVariable.h"
#include "minijavab/core/ir/Function.h"

namespace MiniJavab {
namespace Core {
namespace IR {

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

StructType* Module::GetStructTypeByName(std::string name) const {
    return nullptr;
}

void Module::Dump() {
    if (GetNumberOfGlobalVariables() && 
        GetNumberOfFunctions() == 0 &&
        _structTypes.empty()) {
        std::cerr << "Module is empty!\n";
        return;
    }

    std::cout << "; module";
    if (!Name.empty()) {
        std::cout << " \"" << Name << "\"";
    }
    std::cout << "\n";

    if (GetNumberOfGlobalVariables() > 0) {
        std::cout << "; Global Variables\n";
        for (Value* value : GetGlobalVariables()) {
            static_cast<GlobalVariable*>(value)->Dump();
        }
    }
}

}}} // end namespace