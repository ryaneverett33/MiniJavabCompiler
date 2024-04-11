#include "minijavab/core/ir/ValuePrinter.h"

#include "minijavab/core/ir/PrinterImpl.h"
#include "minijavab/core/ir/Value.h"

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

void ValuePrinter::Print(std::ostream& out, const Value* value) {
    std::string valueName;
    
    // search for the value in the map
    std::unordered_map<const Value*, std::string>::iterator searchResult = _valueMap.find(value);
    if (searchResult != _valueMap.end()) {
        valueName = searchResult->second;
    }
    else {
        if (value->HasName()) {
            valueName = value->Name;
        }
        else {
            valueName = std::to_string(_temporaryCount);
            _temporaryCount += 1;
        }

        _valueMap.insert({value, valueName});
    }

    out << value->ValueType->GetString() << " %" << valueName;
}

void ValuePrinter::PrintNoType(std::ostream& out, const Value* value) {
    std::string valueName;
    
    // search for the value in the map
    std::unordered_map<const Value*, std::string>::iterator searchResult = _valueMap.find(value);
    if (searchResult != _valueMap.end()) {
        valueName = searchResult->second;
    }
    else {
        if (value->HasName()) {
            valueName = value->Name;
        }
        else {
            valueName = std::to_string(_temporaryCount);
            _temporaryCount += 1;
        }

        _valueMap.insert({value, valueName});
    }

    out << "%" << valueName;
}

}}} // end namespace