#pragma once
#include <string>
#include <stdio.h>
#include "Node.h"

namespace MiniJavab {
namespace AST {

class TypeNode : public Node {
    public:
        TypeNode() : Node({}) {}
};

class IntegerTypeNode : public TypeNode {
    public:
        IntegerTypeNode() : TypeNode() {}
        void Dbg() { printf("Integer Type\n"); }
};

class BooleanTypeNode : public TypeNode {
    public:
        BooleanTypeNode() : TypeNode() {}
        void Dbg() { printf("Boolean Type\n"); }
};

class ObjectTypeNode : public TypeNode {
    public:
        ObjectTypeNode(std::string objectType);
        void Dbg() { printf("%s Type\n", ObjectType.c_str()); }

        std::string ObjectType;
};

class ArrayTypeNode : public TypeNode {
    public:
        ArrayTypeNode(TypeNode* baseType, int dimensions=1);
        void Increase();
        void Dbg();

        TypeNode* BaseType;
        int Dimensions;
};

}} // end namespace