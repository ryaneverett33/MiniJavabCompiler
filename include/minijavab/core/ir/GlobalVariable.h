#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class Constant;

class GlobalVariable : public Value {
    public:
        GlobalVariable(std::string name, Constant* value)
            : Name(name),
            Value(value) {}

        std::string Name;
        Constant* Value = nullptr;
};

}}} // end namespace