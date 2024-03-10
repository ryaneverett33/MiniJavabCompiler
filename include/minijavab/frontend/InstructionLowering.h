#pragma once
#include "minijavab/frontend/frontend.h"

namespace MiniJavab {
namespace Core {
namespace IR {
    class Function;
}} // end Core::IR namespace

namespace Frontend {
class ASTConverter;
class ASTMethod;

class InstructionLowering {
    public:
        InstructionLowering(ASTConverter* converter);

        void LowerFunction(ASTMethod* methodDefinition, Core::IR::Function* function);

    private:
        ASTConverter* _converter = nullptr;
};

}} // end namespace