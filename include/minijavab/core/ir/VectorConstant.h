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

class VectorConstant : public AggregateConstant {
    public:
        VectorConstant(Type* type, std::initializer_list<Constant*> values);
        VectorConstant(Type* type, std::vector<Constant*> values);
        virtual void Print(std::ostream& out = std::cerr) const override;
};

}}} // end namespace