#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"
#include "minijavab/core/ir/VectorConstant.h"

namespace MiniJavab {
namespace Core {
namespace IR {

class StringConstant : public VectorConstant {
    public:
        StringConstant(std::string value);
        virtual void Print(std::ostream& out = std::cerr) const override;

        std::string GetString() const { return _stringValue; }
    private:
        std::string _stringValue;
};

}}} // end namespace