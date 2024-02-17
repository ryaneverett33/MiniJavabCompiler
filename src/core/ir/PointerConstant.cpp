#include "minijavab/core/ir/PointerConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

PointerConstant::PointerConstant(Type* type)
    : Constant(type, ConstantKind::Pointer) {}

NullPointerConstant::NullPointerConstant(Type* type)
    : PointerConstant(type) {}

Value* NullPointerConstant::GetPointerTarget() const {
    return nullptr;
}

void NullPointerConstant::Print(std::ostream& out) const {
    out << "null";
}

}}} // end namespace