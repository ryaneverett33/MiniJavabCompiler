#include "minijavab/core/ir/StringConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

StringConstant::StringConstant(std::string value)
    : VectorConstant(IR::StringType(), {}),
    _stringValue(value) {}

void StringConstant::Print(std::ostream& out) const {
    out << "\"" << _stringValue << "\"";
}

}}} // end namespace