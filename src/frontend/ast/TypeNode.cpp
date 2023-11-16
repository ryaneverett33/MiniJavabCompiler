#include "minijavab/frontend/ast/TypeNode.h"

namespace MiniJavab {
namespace Frontend {
namespace AST {

ObjectTypeNode::ObjectTypeNode(std::string objectType)
    : TypeNode(TypeNodeKind::Object),
    ObjectType(objectType) {}

ArrayTypeNode::ArrayTypeNode(TypeNode* baseType, int dimensions)
    : TypeNode(TypeNodeKind::Array),
    BaseType(baseType),
    Dimensions(dimensions) {}

void ArrayTypeNode::Dump(std::ostream& out) {
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
    out << baseStr;
    for (int i = 0; i < Dimensions; i++) {
        out << "[]";
    }
    out << " Type" << std::endl;
}

void ArrayTypeNode::Str(std::ostream& out) {
    BaseType->Str(out);
    for (int i = 0; i < Dimensions; i++) {
        out << "[]";
    }
}

}}} // end namespace