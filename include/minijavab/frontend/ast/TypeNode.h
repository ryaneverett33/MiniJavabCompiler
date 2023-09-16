#pragma once
#include <string>
#include <stdio.h>
#include "minijavab/frontend/ast/Node.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

enum class TypeNodeKind {
    Integer,
    String,
    Boolean,
    Void,
    Object,
    Array
};

class TypeNode : public Node {
    public:
        TypeNode(TypeNodeKind kind) : Node(),
        Kind(kind) {}
        virtual bool IsIntegerType() { return Kind == TypeNodeKind::Integer; }
        virtual bool IsVoidType() { return Kind == TypeNodeKind::Void; }
        virtual bool IsStringType() { return Kind == TypeNodeKind::String; }
        virtual bool IsBooleanType() { return Kind == TypeNodeKind::Boolean; }
        virtual bool IsObjectType() { return Kind == TypeNodeKind::Object; }
        virtual bool IsArrayType() { return Kind == TypeNodeKind::Array; }
        
        TypeNodeKind Kind;
};

class IntegerTypeNode : public TypeNode {
    public:
        IntegerTypeNode() : TypeNode(TypeNodeKind::Integer) {}
        void Dump(std::ostream& out=std::cout) override { out << "Integer Type" << std::endl; }
        void Str(std::ostream& out) override { out << "int"; }
};

class StringTypeNode : public TypeNode {
    public:
        StringTypeNode() : TypeNode(TypeNodeKind::String) {}
        void Dump(std::ostream& out=std::cout) override { out << "String Type" << std::endl; }
        void Str(std::ostream& out) override { out << "String"; }
};

class BooleanTypeNode : public TypeNode {
    public:
        BooleanTypeNode() : TypeNode(TypeNodeKind::Boolean) {}
        void Dump(std::ostream& out=std::cout) override { out << "Boolean Type" << std::endl; }
        void Str(std::ostream& out) override { out << "boolean"; }
};

class VoidTypeNode : public TypeNode {
    public:
        VoidTypeNode() : TypeNode(TypeNodeKind::Void) {}
        void Dump(std::ostream& out=std::cout) override { out << "Void Type" << std::endl; }
        void Str(std::ostream& out) override { out << "void"; }
};

class ObjectTypeNode : public TypeNode {
    public:
        ObjectTypeNode(std::string objectType);
        void Dump(std::ostream& out=std::cout) override { out << ObjectType << " Type" << std::endl; }
        void Str(std::ostream& out) override { out << ObjectType; }

        std::string ObjectType;
};

class ArrayTypeNode : public TypeNode {
    public:
        ArrayTypeNode(TypeNode* baseType, int dimensions=1);
        void Increase() { Dimensions += 1; }
        void Dump(std::ostream& out=std::cout) override;
        void Str(std::ostream& out) override;

        TypeNode* BaseType;
        int Dimensions;
};

}}} // end namespace