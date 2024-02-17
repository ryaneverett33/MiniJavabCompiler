#include "minijavab/core/ir/Constant.h"
#include "minijavab/core/ir/IntegerConstant.h"
#include "minijavab/core/ir/StructConstant.h"
#include "minijavab/core/ir/VectorConstant.h"
#include "minijavab/core/ir/PointerConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {
Constant::Constant(IR::Type* type, ConstantKind kind)
            : Value(type),
            _kind(kind) {}

Constant* Constant::GetNull(Type* type) {
    switch (type->GetTypeKind()) {
        case TypeKind::Boolean:
        case TypeKind::Integer:
            return new IntegerConstant(type, 0);
        case TypeKind::Struct:
            return new StructConstant(type, {});
        case TypeKind::Vector:
            return new VectorConstant(type, {});
        case TypeKind::Pointer:
            return new NullPointerConstant(type);
        case TypeKind::Void:
            assert(false && "Cannot create a null void constant!");
        default:
            assert(false && "Not implemented yet");
    }
}

}}} // end namespace