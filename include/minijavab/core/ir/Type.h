#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include <initializer_list>
#include <vector>
#include <iostream>

namespace MiniJavab {
namespace Core {
namespace IR {

/// The "type" of this Type
enum class TypeKind {
    Integer,
    Boolean,
    Void,
    Struct,
    Vector,
    Pointer,
    Function
};

/// Abstract class describing a Type
class Type {
    public:
        /// Get a string representation of a given type
        /// @return The string representation of the type
        virtual std::string GetString() const = 0;

        /// Whether or not this type is an IntegerType
        virtual bool IsIntegerType() const { return false; }

        /// Whether or not this type is a BooleanType
        virtual bool IsBooleanType() const { return false; }

        /// Whether or not this type is a VoidType
        virtual bool IsVoidType() const { return false; }

        /// Whether or not this type is a StructType
        virtual bool IsStructType() const { return false; }

        /// Whether or not this type is a VectorType
        virtual bool IsVectorType() const { return false; }

        /// Whether or not this type is a PointerType
        virtual bool IsPointerType() const { return false; }

        /// Whether or not this type is a compound FunctionType
        virtual bool IsFunctionType() const { return false; }

        /// Get the underlying kind for this type. May be used
        /// in place of dynamic_cast.
        /// @return The kind of this type
        virtual TypeKind GetTypeKind() const = 0;
};

/// Describes signed and unsigned integers of different widths
class IntegerType : public Type {
    public:
        IntegerType(uint8_t bitWidth, bool isSigned=true);
        virtual std::string GetString() const override;
        virtual bool IsIntegerType() const override;
        virtual TypeKind GetTypeKind() const override;

        /// Get the number of bits required to represent this integer
        /// @return The number of bits required
        uint8_t GetBitWidth() const;

        /// Whether or not this is a signed integer or unsigned integer
        /// @return True if it's a signed integer, false otherwise
        bool IsSigned() const;

    private:
        /// The width (number of bits required) for the integer
        uint8_t _bitWidth;

        /// Whether this is a signed integer
        bool _isSigned;
};

/// Describes true/false boolean values
class BooleanType : public IntegerType {
    public:
        BooleanType();

        virtual std::string GetString() const override;
        virtual bool IsBooleanType() const override;
        virtual bool IsIntegerType() const override;
        virtual TypeKind GetTypeKind() const override;
};

/// Describes a void type. Void types can only be used by function and function pointers.
class VoidType : public Type {
    public:
        virtual std::string GetString() const override;
        virtual bool IsVoidType() const override;
        virtual TypeKind GetTypeKind() const override;
};

/// Describes a structure type that contains multiple types within it.
class StructType : public Type {
    public:
        /// Create a new structure type with a given name
        /// @param name Name of the structure
        /// @param types Types of values within the structure
        StructType(std::string name, std::initializer_list<Type*> types);

        virtual std::string GetString() const override;
        virtual bool IsStructType() const override;
        virtual TypeKind GetTypeKind() const override;

        // todo: is this used?
        void Dump() const;

        /// The common name of the structure
        std::string Name;

        /// The types of the elements contained within the structure
        std::vector<Type*> ElementTypes;
};

/// Describes a homogenous array type that contains multiple elements
class VectorType : public Type {
    public:
        /// Create a new vector type
        /// @param elementType The type of elements this vector contains
        VectorType(Type* elementType);
        virtual std::string GetString() const override;
        virtual bool IsVectorType() const override;
        virtual TypeKind GetTypeKind() const override;

        /// The type of elements contained in the vector
        Type* ElementType;
};

// Describes a pointer type that points to element elsewhere in the module
class PointerType : public Type {
    public:
        /// Creates a new pointer type
        /// @param elementType The type of the target element
        PointerType(Type* elementType);

        virtual std::string GetString() const override;
        virtual bool IsPointerType() const override;
        virtual TypeKind GetTypeKind() const override;

        /// The type of the element pointed to by this type
        Type* ElementType;
};

/// Describes a compound function type that has a return type and multiple parameter types
class FunctionType : public Type {
    public:
        /// Creates a new function type
        /// @param returnType The return type
        /// @param parameterTypes The parameter types
        FunctionType(Type* returnType, std::initializer_list<Type*> parameterTypes);
        FunctionType(Type* returnType, std::vector<Type*> parameterTypes);

        virtual std::string GetString() const override;
        virtual bool IsFunctionType() const override;
        virtual TypeKind GetTypeKind() const override;

        /// The return type, may be a void type
        Type* ReturnType;

        /// The parameter types
        std::vector<Type*> ParameterTypes;
};

/// Helper function for creating a "StringType"
/// @note StringTypes are the same as vector<i8> types
/// @return A new "StringType" object
inline VectorType* StringType() {
    return new VectorType(new IntegerType(8));
} 

}}} // end namespace