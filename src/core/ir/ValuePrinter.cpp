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

std::string ValuePrinter::getName(const Value* value) {
    // search for the value in the map
    std::unordered_map<const Value*, std::string>::iterator searchResult = _valueMap.find(value);
    if (searchResult != _valueMap.end()) {
        return searchResult->second;
    }
    else {
        std::string valueName;
        if (value->HasName()) {
            valueName = value->Name;
        }
        else {
            valueName = std::to_string(_temporaryCount);
            _temporaryCount += 1;
        }

        _valueMap.insert({value, valueName});
        return valueName;
    }
}

void ValuePrinter::Print(std::ostream& out, const Value* value) {
    std::string valueName = getName(value);
    out << value->ValueType->GetString() << " %" << valueName;
}

void ValuePrinter::PrintNoType(std::ostream& out, const Value* value) {
    std::string valueName = getName(value);
    out << "%" << valueName;
}

}}} // end namespace