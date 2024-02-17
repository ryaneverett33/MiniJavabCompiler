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
        Constant* GetElement(size_t elementIndex);
    protected:
        std::vector<Constant*> _values;
};

}}} // end namespace