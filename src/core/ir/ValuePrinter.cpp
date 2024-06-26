#include "minijavab/core/ir/ValuePrinter.h"

#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Immediate.h"

namespace MiniJavab {
namespace Core {
namespace IR {

PrinterImpl ValuePrinter::Initialize() {
    _instance = new ValuePrinter();
    return _instance->createImpl();
}
PrinterImpl ValuePrinter::Get() {
    if (_instance == nullptr) {
        return Initialize();
    }
    return _instance->createImpl();
}
PrinterImpl ValuePrinter::createImpl() {
    _instanceCount += 1;
    return PrinterImpl(_instance);
}
void ValuePrinter::implWasDestroyed() {
    _instanceCount -= 1;
    if (_instanceCount == 0) {
        delete _instance;
        _instance = nullptr;
    }
}

std::string ValuePrinter::getName(const Value* value) {
    // search for the value in the map and return it if it exists
    std::unordered_map<const Value*, std::string>::iterator searchResult = _valueMap.find(value);
    if (searchResult != _valueMap.end()) {
        return searchResult->second;
    }
    else {
        // if the value doesn't exist in the map, figure out its name and add it
        std::string valueName;
        if (value->HasName()) {
            valueName = value->Name;
        }
        else {
            // If the value is unnamed, assign it a temporary id
            valueName = std::to_string(_temporaryCount);
            _temporaryCount += 1;
        }

        // insert the value and its name into the map and then return the name
        _valueMap.insert({value, valueName});
        return valueName;
    }
}

void ValuePrinter::PrintNoType(std::ostream& out, const Value* value) {
    if (const Immediate* immediate = dynamic_cast<const Immediate*>(value)) {
        out << "";
        value->Print(out);
    }
    else {
        std::string valueName = getName(value);
        out << "%" << valueName;
    }
}

void ValuePrinter::Print(std::ostream& out, const Value* value) {
    if (value->ValueType->IsFunctionType()) {
        FunctionType* functionType = static_cast<FunctionType*>(value->ValueType);
        out << functionType->ReturnType->GetString() << " ";
    }
    else {
        out << value->ValueType->GetString() << " ";
    }
    PrintNoType(out, value);
}

}}} // end namespace