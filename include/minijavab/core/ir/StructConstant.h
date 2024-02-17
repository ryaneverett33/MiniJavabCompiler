#pragma once
#include <string>
#include <map>
#include <vector>
#include <initializer_list>

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {
class Constant;

class StructConstant : public Constant {
    public:
        StructConstant(Type* type, std::initializer_list<Constant*> values);
        Constant* GetElement(size_t elementIndex);
    private:
        std::vector<Constant*> _values;
};

}}} // end namespace