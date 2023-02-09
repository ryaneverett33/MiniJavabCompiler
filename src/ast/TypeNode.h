#pragma once
#include <string>
#include <stdio.h>
#include "Node.h"

namespace MiniJavab {
namespace AST {

class TypeNode : public Node {
    public:
        TypeNode() : Node() {}
};

class IntegerTypeNode : public TypeNode {
    public:
        IntegerTypeNode() : TypeNode() {}
        void Dump(std::ostream& out=std::cout) override { out << "Integer Type" << std::endl; }
        void Str(std::ostream& out) override { out << "int"; }
};

class StringTypeNode : public TypeNode {
    public:
        StringTypeNode() : TypeNode() {}
        void Dump(std::ostream& out=std::cout) override { out << "String Type" << std::endl; }
        void Str(std::ostream& out) override { out << "String"; }
};

class BooleanTypeNode : public TypeNode {
    public:
        BooleanTypeNode() : TypeNode() {}
        void Dump(std::ostream& out=std::cout) override { out << "Boolean Type" << std::endl; }
        void Str(std::ostream& out) override { out << "boolean"; }
};

class VoidTypeNode : public TypeNode {
    public:
        VoidTypeNode() : TypeNode() {}
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

}} // end namespace