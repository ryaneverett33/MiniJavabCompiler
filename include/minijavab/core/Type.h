#pragma once
#include <string>
#include <initializer_list>
#include <vector>

namespace MiniJavab {
namespace Core {

enum class TypeKind {
    Integer,
    Void,
    String,
    Boolean,
    Object,
    Method,
    Array
};

class Type {
    public:
        virtual bool IsIntegerType() { return Kind == TypeKind::Integer; }
        virtual bool IsVoidType() { return Kind == TypeKind::Void; }
        virtual bool IsStringType() { return Kind == TypeKind::String; }
        virtual bool IsBooleanType() { return Kind == TypeKind::Boolean; }
        virtual bool IsObjectType() { return Kind == TypeKind::Object; }
        virtual bool IsMethodType() { return Kind == TypeKind::Method; }
        virtual bool IsArrayType() { return Kind == TypeKind::Array; }
        virtual bool Equals(Type* other) {
            if (other == nullptr) { return false; }
            return Kind == other->Kind;
        }
    protected:
        Type(TypeKind kind) :
            Kind(kind) {}

        TypeKind Kind;
};

class IntegerType : public Type {
    public:
        IntegerType() : Type(TypeKind::Integer) {}
};
class VoidType : public Type {
    public:
        VoidType() : Type(TypeKind::Void) {}
};
class StringType : public Type {
    public:
        StringType() : Type(TypeKind::String) {}
};
class BooleanType : public Type {
    public:
        BooleanType() : Type(TypeKind::Boolean) {}
};
class ObjectType : public Type {
    public:
        ObjectType(std::string typeName) : Type(TypeKind::Object),
            TypeName(typeName) {}
        bool Equals(Type* other) override;

        std::string TypeName;
};
class MethodType : public Type {
    public:
        MethodType(Type* returnType, std::initializer_list<Type*> parameterTypes) : Type(TypeKind::Method),
            ReturnType(returnType),
            ParameterTypes(parameterTypes) {}
        bool Equals(Type* other) override;

        Type* ReturnType;
        std::vector<Type*> ParameterTypes;
};
class ArrayType : public Type {
    public:
        ArrayType(Type* baseType, int dimensions) : Type(TypeKind::Array),
            BaseType(baseType),
            Dimensions(dimensions) {}
        bool Equals(Type* other) override;

        Type* BaseType;
        int Dimensions;
};

}} // end namespace