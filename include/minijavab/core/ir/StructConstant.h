#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/AggregateConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {
class Constant;

class StructConstant : public AggregateConstant {
    public:
        StructConstant(Type* type, std::initializer_list<Constant*> values);
        virtual void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace