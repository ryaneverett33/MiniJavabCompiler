#include "minijavab/core/ir/Module.h"

#include <iostream>
#include <cassert>

#include "minijavab/core/ir/Type.h"
#include "minijavab/core/ir/GlobalVariable.h"
#include "minijavab/core/ir/Function.h"
#include "minijavab/core/ir/StringConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Module::Module(std::string name)
    : Name(name) {}

void Module::addFunctionHelper(Function* function) {
    _symbolTable.push_back(function);
    _functionCount += 1;

    function->_containingModule = this;
}

void Module::AddFunction(Function* function) {
    assert(GetFunctionByName(function->Name) == nullptr && "Function already registered!");
    assert(dynamic_cast<IntrinsicFunction*>(function) == nullptr && "Can't register custom intrinsic functions");

    // error if the function shares a name with an intrinsic, these function names are reserved
    // see GetIntrinsic()
    if (function->Name == MJ_PRINTLN_STR_INTRINSIC ||
        function->Name == MJ_PRINTLN_INT_INTRINSIC ) {
        throw std::invalid_argument("Can't add a function named '" + function->Name + "' as it's an intrinsic function");
    }
    addFunctionHelper(function);
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

GlobalVariable* Module::AddStringConstant(std::string value) {
    GlobalVariable* stringVariable = new GlobalVariable("str." + std::to_string(_stringConstantCount), 
        new StringConstant(value)
    );

    AddGlobalVariable(stringVariable);
    _stringConstantCount += 1;

    return stringVariable;
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

IntrinsicFunction* Module::GetIntrinsic(std::string name) {
    // Lookup procedure
    // Check if the intrinsic has already been registered
    // If it has already been registered, return it
    // If it hasn't been registered, register it and then return it
    if (name != MJ_PRINTLN_STR_INTRINSIC && name != MJ_PRINTLN_INT_INTRINSIC) {
        throw std::invalid_argument("Unknown intrinsic!");
    }

    // Check if the intrinsic has already been registered
    Function* function = GetFunctionByName(name);
    if (function != nullptr) {
        // we don't need to sanity check the type because AddFunction restricts adding intrinsics
        return static_cast<IntrinsicFunction*>(function);
    }

    // If it doesn't already exist, create it and add it to the list
    if (name == MJ_PRINTLN_STR_INTRINSIC) {
        IntrinsicFunction* intrinsic = new IntrinsicFunction(MJ_PRINTLN_STR_INTRINSIC, new FunctionType(
            new VoidType(),
            {new PointerType(StringType())}
        ));

        addFunctionHelper(intrinsic);
        return intrinsic;
    }
    else if (name == MJ_PRINTLN_INT_INTRINSIC) {
        IntrinsicFunction* intrinsic = new IntrinsicFunction(MJ_PRINTLN_INT_INTRINSIC, new FunctionType(
            new VoidType(),
            {new IntegerType(32)}
        ));

        addFunctionHelper(intrinsic);
        return intrinsic;
    }

    // if we get here, then a new intrinsic needs to be added or something horribly bad has happened
    assert(false && "unreachable");
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