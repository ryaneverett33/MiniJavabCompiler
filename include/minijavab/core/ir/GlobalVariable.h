#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/Constant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class GlobalVariable : public Value {
    public:
        GlobalVariable(std::string name, Constant* value);
        void Dump() const;
        void Print(std::ostream& out = std::cerr) const;

        std::string Name;
        Constant* Initializer;
};

}}} // end namespace