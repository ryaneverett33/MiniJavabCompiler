#include "minijavab/core/ir/Function.h"

#include "minijavab/core/ir/BasicBlock.h"
#include "minijavab/core/ir/ValuePrinter.h"
#include "minijavab/core/ir/PrinterImpl.h"

namespace MiniJavab {
namespace Core {
namespace IR {

Function::Function(std::string name, FunctionType* type)
    : Value(type, name) {
    // Construct the parameter list
    _parameterList.resize(type->ParameterTypes.size());
    for (size_t i = 0; i < type->ParameterTypes.size(); i++)
    {
        _parameterList[i] = new Parameter(type->ParameterTypes[i], i);
    }
}

void Function::Print(std::ostream& out) const {
    PrinterImpl printer = ValuePrinter::Initialize();
    FunctionType* functionType = static_cast<FunctionType*>(ValueType);

    out << functionType->ReturnType->GetString() << " " << Name << " (";
    for (size_t i = 0; i < _parameterList.size(); i++) {
        const Parameter* parameter = _parameterList[i];

        parameter->Print(out);
        if ((i + 1) < _parameterList.size()) {
            out << ", ";
        }
    }
    out << ")";

    if (!IsDefined()) {
        out << ";";
    }
    else {
        out << "\n";

        uint64_t temporaryCounter = 0;
        for (BasicBlock* block : _basicBlocks) {
            printer.PrintNoType(out, block);
            out << ":\n";

            for (Instruction* inst : block->Instructions) {
                out << "\t";
                inst->Print(out);
                out << "\n";
            }
        }
    }
}

void Function::AppendBasicBlock(BasicBlock* block) {
    _basicBlocks.push_back(block);

    block->ParentFunction = this;
    block->Position = std::prev(_basicBlocks.end());
}

BasicBlock* Function::CreateBlock(std::string name) {
    BasicBlock* block = new BasicBlock(name);
    AppendBasicBlock(block);

    return block;
}

std::vector<Parameter*> Function::GetParameters() const {
    return _parameterList;
}

Parameter* Function::GetParameterByName(std::string name) const {
    for (Parameter* parameter: _parameterList) {
        if (parameter->HasName() && parameter->Name == name) {
            return parameter;
        }
    }
    return nullptr;
}

Parameter* Function::GetParameterByIndex(size_t index) const {
    if (index < _parameterList.size()) {
        return _parameterList[index];
    }

    return nullptr;
}

std::list<BasicBlock*>* Function::GetBlocks() {
    return &(_basicBlocks);
}

bool Function::IsDefined() const {
    return !_basicBlocks.empty();
}

Module* Function::GetContainingModule() const {
    return _containingModule;
}

}}} // end namespace