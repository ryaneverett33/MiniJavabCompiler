#pragma once
#include <string>
#include <optional>
#include <list>

namespace MiniJavab {
namespace Core {
namespace IR {

class BasicBlock {
    public:
        std::optional<std::list<BasicBlock*>::iterator> Next = std::nullopt;
        std::optional<std::list<BasicBlock*>::iterator> Previous = std::nullopt;
};

}}} // end namespace