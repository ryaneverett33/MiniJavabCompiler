#pragma once
#include <string>
#include <map>
#include <list>

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock;

class Function : public Value {
    public:
        std::list<BasicBlock*> BasicBlocks;

        std::string Name;
};

}}} // end namespace