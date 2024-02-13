#pragma once
#include <string>
#include <sstream>
#include <stdexcept>
#include <initializer_list>
#include <vector>

namespace MiniJavab {
namespace Core {
namespace IR {

enum class TypeKind {
    Integer,
    Boolean,
    Void,
    Struct,
    Vector,
    Pointer,
    Function
};

class Type {
    public:
        virtual std::string GetString() const = 0;
        virtual bool IsIntegerType() const { return false; }
        virtual bool IsBooleanType() const { return false; }
        virtual bool IsVoidType() const { return false; }
        virtual bool IsStructType() const { return false; }
        virtual bool IsVectorType() const { return false; }
        virtual bool IsPointerType() const { return false; }
        virtual bool IsFunctionType() const { return false; }
        /*static bool Equals(Type* a, Type* b) {

        }*/
    protected:
        virtual TypeKind GetTypeKind() const = 0;
};

class IntegerType : public Type {
    public:
        IntegerType(uint8_t bitWidth) {
            if (bitWidth != 1 && bitWidth != 8 && bitWidth != 32) {
                throw std::invalid_argument("Invalid bit width!");
            }
            _bitWidth = bitWidth;
        }
        virtual std::string GetString() const override {
            return "i" + std::to_string(_bitWidth);
        }
        uint8_t GetBitWidth() {
            return _bitWidth;
        }
        virtual bool IsIntegerType() const override { return true; }

    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Integer;
        }

        uint8_t _bitWidth;
};

class BooleanType : public IntegerType {
    public:
        BooleanType()
            : IntegerType(1) {}

        virtual std::string GetString() const override {
            return "bool";
        }
        virtual bool IsBooleanType() const override { return true; }
    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Boolean;
        }
};

class VoidType : public Type {
    public:
        virtual std::string GetString() const override {
            return "void";
        }
        virtual bool IsVoidType() const override { return true; }
    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Void;
        }
};

class StructType : public Type {
    public:
        StructType(std::string name, std::initializer_list<Type*> types)
            : Name(name),
            ContainedTypes(types) {}

        virtual std::string GetString() const override {
            return "%" + Name;
        }
        void Dump() const {
            std::cerr << GetString() << " = type { ";
            for (size_t i = 0; i < ContainedTypes.size(); i++) {
                std::cerr << ContainedTypes[i]->GetString();
                if ((i + 1) < ContainedTypes.size()) {
                    std::cerr << ", ";
                }
            }
            std::cerr << " }\n";
        }
        virtual bool IsStructType() const override { return true; }

        std::string Name;
        std::vector<Type*> ContainedTypes;
    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Struct;
        }
};

class VectorType : public Type {
    public:
        VectorType(Type* elementType)
            : ElementType(elementType) {}
        virtual std::string GetString() const override {
            return "vector<" + ElementType->GetString() + ">";
        }
        virtual bool IsVectorType() const override { return true; }

        Type* ElementType;
    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Vector;
        }
};

class PointerType : public Type {
    public:
        PointerType(Type* elementType)
            : ElementType(elementType) {}

        virtual std::string GetString() const override {
            return ElementType->GetString() + "*";
        }
        virtual bool IsPointerType() const override { return true; }

        Type* ElementType;
    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Pointer;
        }
};

class FunctionType : public Type {
    public:
        FunctionType(Type* returnType, std::initializer_list<Type*> parameterTypes)
            : ReturnType(returnType),
            ParameterTypes(parameterTypes) {}

        virtual std::string GetString() const override {
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
        bool IsFunctionType() const override { return true; }

        Type* ReturnType;
        std::vector<Type*> ParameterTypes;
    private:
        virtual TypeKind GetTypeKind() const override {
            return TypeKind::Function;
        }
};

}}} // end namespace