#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class PointerConstant : public Constant {
    public:
        PointerConstant(Type* type);
        virtual Value* GetPointerTarget() const = 0;
};

class NullPointerConstant : public PointerConstant {
    public:
        NullPointerConstant(Type* type);
        virtual Value* GetPointerTarget() const override;
        virtual void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace