#include "TypeNode.h"

namespace MiniJavab {
namespace AST {

ObjectTypeNode::ObjectTypeNode(std::string objectType)
    : TypeNode(),
    ObjectType(objectType) {}

ArrayTypeNode::ArrayTypeNode(TypeNode* baseType, int dimensions)
    : TypeNode(),
    BaseType(baseType),
    Dimensions(dimensions) {}

void ArrayTypeNode::Increase() { Dimensions += 1; }
void ArrayTypeNode::Dbg() {
    std::string baseStr;
    if (dynamic_cast<IntegerTypeNode*>(BaseType)) {
        baseStr = "Integer";
    }
    else if (dynamic_cast<BooleanTypeNode*>(BaseType)) {
        baseStr = "Boolean";
    }
    else {
        ObjectTypeNode* objectType = dynamic_cast<ObjectTypeNode*>(BaseType);
        baseStr = objectType->ObjectType;
    }
    printf("%s", baseStr.c_str());
    for (int i = 0; i < Dimensions; i++) {
        printf("[]");
    }
    printf(" Type\n");
}

}} // end namespace