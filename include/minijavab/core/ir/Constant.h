#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

enum class ConstantKind {
    Integer,
    String,
    Struct,
    Vector
};

class Constant : public Value {
    public:
        Constant(IR::Type* type, ConstantKind kind)
            : Value(type),
            _kind(kind) {}

        ConstantKind GetKind() const { return _kind; }
        void Dump() const;
        virtual void Print(std::ostream& out = std::cerr) const = 0;
    private:
        ConstantKind _kind;
};

}}} // end namespace