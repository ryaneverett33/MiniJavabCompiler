#include "minijavab/frontend/ast/Type.h"
#include <sstream>

namespace MiniJavab {
namespace Frontend {
namespace AST {

bool ObjectType::Equals(Type* other) {
    // Verify other is an object type
    if (!Type::Equals(other)) {
        return false;
    }
    ObjectType* otherObjectType = static_cast<ObjectType*>(other);

    return TypeName == otherObjectType->TypeName;
}

bool MethodType::Equals(Type* other) {
    // Verify other is a method type
    if (!Type::Equals(other)) {
        return false;
    }
    MethodType* otherMethodType = static_cast<MethodType*>(other);

    // Verify the return types are the same
    if (!ReturnType->Equals(otherMethodType->ReturnType)) {
        return false;
    }

    // Verify parameter types are the same
    if (ParameterTypes.size() != otherMethodType->ParameterTypes.size()) {
        return false;
    }
    for (size_t i = 0; i < ParameterTypes.size(); i++) {
        if (!ParameterTypes[i]->Equals(otherMethodType->ParameterTypes[i])) {
            return false;
        }
    }
    return true;
}

bool ArrayType::Equals(Type* other) {
    // Verify other is an array type
    if (!Type::Equals(other)) {
        return false;
    }
    ArrayType* otherArrayType = static_cast<ArrayType*>(other);

    // Verify base types are the same
    if (!BaseType->Equals(otherArrayType->BaseType)) {
        return false;
    }

    return Dimensions == otherArrayType->Dimensions;
}

std::string ArrayType::GetName() const {
    std::stringstream builder;
    builder << BaseType->GetName();
    for (int i = 0; i < Dimensions; i++) {
        builder << "[]";
    }
    return builder.str();
}

}}} // end namespace