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
    Vector,
    Pointer
};

class Constant : public Value {
    public:
        Constant(IR::Type* type, ConstantKind kind);

        ConstantKind GetKind() const { return _kind; }
        void Dump() const;
        virtual void Print(std::ostream& out = std::cerr) const = 0;
        static Constant* GetNull(Type* type);
    private:
        ConstantKind _kind;
};

}}} // end namespace