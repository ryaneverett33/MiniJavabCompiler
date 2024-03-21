#include "minijavab/core/ir/IntegerConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IntegerConstant::IntegerConstant(IR::Type* type, Immediate* value)
    : Constant(type, ConstantKind::Integer),
    Value(value) {
    //assert(type->IsIntegerType());
    
    // todo do bit width checking
}

void IntegerConstant::Print(std::ostream& out) const {
    Value->Print(out);
}

BooleanConstant::BooleanConstant(bool value)
    : IntegerConstant(new IR::BooleanType(), 
                    new Immediate(new IR::BooleanType(), value))
    {}

void BooleanConstant::Print(std::ostream& out) const {
    out << std::boolalpha << Value->GetBoolean();
}

}}} // end namespace