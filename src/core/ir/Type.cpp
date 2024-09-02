#include "minijavab/core/ir/Type.h"

namespace MiniJavab {
namespace Core {
namespace IR {

// IntegerType definitions

Type::Type(std::string name)
    : Name(name)
    {}

Type* Type::StripPointerCasts() {
    if (IsPointerType()) {
        PointerType* pointerType = static_cast<PointerType*>(this);
        return pointerType->ElementType;
    }
    return this;
}

IntegerType::IntegerType(uint8_t bitWidth, bool isSigned, std::string name)
    : Type(name),
    _isSigned(isSigned) {
    if (bitWidth != 1 && bitWidth != 8 && bitWidth != 32) {
        throw std::invalid_argument("Invalid bit width!");
    }
    _bitWidth = bitWidth;
}

std::string IntegerType::GetString() const {
    return "i" + std::to_string(_bitWidth);
}

uint8_t IntegerType::GetBitWidth() const { return _bitWidth; }

bool IntegerType::IsSigned() const { return _isSigned; }

bool IntegerType::IsIntegerType() const { return true; }

TypeKind IntegerType::GetTypeKind() const {
    return TypeKind::Integer;
}
size_t IntegerType::GetSize() const {
    return GetBitWidth() / 8;
}

// BooleanType definitions

BooleanType::BooleanType(std::string name)
    : IntegerType(1, false, name) {}

std::string BooleanType::GetString() const {
    return "bool";
}
bool BooleanType::IsBooleanType() const { return true; }
bool BooleanType::IsIntegerType() const { return false; }
TypeKind BooleanType::GetTypeKind() const {
    return TypeKind::Boolean;
}

// VoidType definitions

std::string VoidType::GetString() const {
    return "void";
}
bool VoidType::IsVoidType() const { return true; }
TypeKind VoidType::GetTypeKind() const {
    return TypeKind::Void;
}
size_t VoidType::GetSize() const {
    return 0;
}

// StructType definitions

StructType::StructType(std::string name, std::initializer_list<Type*> types)
            : Type(name),
            ElementTypes(types) {
    for (Type* elementType: types) {
        if (elementType->Name.empty()) {
            throw std::invalid_argument("types");
        }
    }
}
size_t StructType::GetElementOffset(std::string name) {
    size_t offset = 0;
    for (Type* elementType: ElementTypes) {
        if (elementType->Name == name) {
            return offset;
        }
        offset += elementType->GetSize();
    }
    assert(false && "struct type with unnamed sub-types!");
}

Type* StructType::GetElementType(std::string name) {
    size_t offset = 0;
    for (Type* elementType: ElementTypes) {
        if (elementType->Name == name) {
            return elementType;
        }
    }
    assert(false && "struct type with unnamed sub-types!");
}

size_t StructType::GetSize() const {
    size_t size = 0;
    for (Type* elementType: ElementTypes) {
        size += elementType->GetSize();
    }
    return size;
}

std::string StructType::GetString() const { return "%" + Name; }
bool StructType::IsStructType() const { return true; }
TypeKind StructType::GetTypeKind() const { return TypeKind::Struct; }

void StructType::Dump() const {
    std::cerr << GetString() << " = type { ";
    for (size_t i = 0; i < ElementTypes.size(); i++) {
        std::cerr << ElementTypes[i]->GetString() << " " << ElementTypes[i]->Name;

        if ((i + 1) < ElementTypes.size()) {
            std::cerr << ", ";
        }
    }
    std::cerr << " }\n";
}

// VectorType definitions

VectorType::VectorType(Type* elementType, std::string name)
    : Type(name),
    ElementType(elementType) {}
std::string VectorType::GetString() const {
    return "vector<" + ElementType->GetString() + ">";
}
bool VectorType::IsVectorType() const { return true; }
TypeKind VectorType::GetTypeKind() const { return TypeKind::Vector; }
size_t VectorType::GetSize() const {
    // TODO: make pointer size of architecture
    return 8;
}

// PointerType definitions

PointerType::PointerType(Type* elementType, std::string name)
    : Type(name),
    ElementType(elementType) {}

std::string PointerType::GetString() const {
    return ElementType->GetString() + "*";
}
bool PointerType::IsPointerType() const { return true; }
TypeKind PointerType::GetTypeKind() const { return TypeKind::Pointer; }
size_t PointerType::GetSize() const {
    // TODO: make pointer size of architecture
    return 8;
}

// FunctionType definitions

FunctionType::FunctionType(Type* returnType, std::initializer_list<Type*> parameterTypes)
            : ReturnType(returnType),
            ParameterTypes(parameterTypes) {}
FunctionType::FunctionType(Type* returnType, std::vector<Type*> parameterTypes)
    : ReturnType(returnType),
    ParameterTypes(parameterTypes) {}

bool FunctionType::IsFunctionType() const { return true; }
TypeKind FunctionType::GetTypeKind() const { return TypeKind::Function; }

std::string FunctionType::GetString() const {
    // EX: void (i8, bool)
    std::stringstream typeName;
    typeName << ReturnType->GetString() << "(";

    for (size_t i = 0; i < ParameterTypes.size(); i++) {
        typeName << ParameterTypes[i]->GetString();

        if ((i + 1) < ParameterTypes.size()) {
            typeName << ", ";
        }
    }
    typeName << ")";
    return typeName.str();
}
size_t FunctionType::GetSize() const {
    // TODO: make pointer size of architecture
    return 8;
}

}}} // end namespace