#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {
class Constant;

class AggregateConstant : public Constant {
    public:
        AggregateConstant(IR::Type* type, std::initializer_list<Constant*> values, ConstantKind kind);
        AggregateConstant(IR::Type* type, std::vector<Constant*> values, ConstantKind kind);
        Constant* GetElement(size_t elementIndex);
        virtual void Print(std::ostream& out = std::cerr) const override;
    protected:
        std::vector<Constant*> _values;
};

}}} // end namespace