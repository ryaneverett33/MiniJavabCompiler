#include "minijavab/core/ir/IRBuilder.h"

#include "minijavab/core/ir/Instructions/Ret.h"
#include "minijavab/core/ir/Instructions/Alloc.h"
#include "minijavab/core/ir/Instructions/Store.h"
#include "minijavab/core/ir/Instructions/Load.h"
#include "minijavab/core/ir/Instructions/GetPtr.h"
#include "minijavab/core/ir/Instructions/Call.h"
#include "minijavab/core/ir/Instructions/Mul.h"
#include "minijavab/core/ir/Instructions/XOR.h"
#include "minijavab/core/ir/Instructions/Add.h"
#include "minijavab/core/ir/Instructions/Sub.h"
#include "minijavab/core/ir/Instructions/Div.h"
#include "minijavab/core/ir/Instructions/Br.h"
#include "minijavab/core/ir/Instructions/BrIf.h"
#include "minijavab/core/ir/Instructions/Cmp.h"
#include "minijavab/core/ir/Instructions/AND.h"
#include "minijavab/core/ir/Instructions/OR.h"

namespace MiniJavab {
namespace Core {
namespace IR {

IRBuilder::IRBuilder(BasicBlock* block)
    : Block(block) {}

Value* IRBuilder::CreateRet() {
    Instruction* instruction = new RetInstruction();
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateRet(Value* value) {
    Instruction* instruction = new RetInstruction(value);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateAlloc(IR::Type* localType, std::string name) {
    Instruction* instruction = new AllocInstruction(localType, name);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateStore(Value* object, Value* pointer) {
    Instruction* instruction = new StoreInstruction(object, pointer);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateLoad(IR::Type* type, IR::Value* pointer) {
    Instruction* instruction = new LoadInstruction(type, pointer);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateGetPtr(IR::GlobalVariable* variable) {
    Instruction* instruction = new GetPtrInstruction(variable);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateCall(IR::Function* function, std::vector<IR::Value*> arguments) {
    Instruction* instruction = new CallInstruction(function, arguments);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateMul(IR::Value* multiplicand, IR::Value* operand) {
    Instruction* instruction = new MulInstruction(multiplicand, operand);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateXOR(IR::Value* x, IR::Value* y) {
    Instruction* instruction = new XORInstruction(x, y);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateAdd(IR::Value* augend, IR::Value* addend) {
    Instruction* instruction = new AddInstruction(augend, addend);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateSub(IR::Value* minuend, IR::Value* subtrahend) {
    Instruction* instruction = new SubInstruction(minuend, subtrahend);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateDiv(IR::Value* dividend, IR::Value* divisor) {
    Instruction* instruction = new DivInstruction(dividend, divisor);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateBr(IR::BasicBlock* target) {
    Instruction* instruction = new BrInstruction(target);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateBrIf(IR::BasicBlock* target, IR::Value* conditional) {
    Instruction* instruction = new BrIfInstruction(target, conditional);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateCmp(ComparisonOperation operation, Value* leftHandSide, Value* rightHandSide) {
    Instruction* instruction = new CmpInstruction(operation, leftHandSide, rightHandSide);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateAND(IR::Value* x, IR::Value* y) {
    Instruction* instruction = new ANDInstruction(x, y);
    Insert(instruction);

    return instruction;
}

Value* IRBuilder::CreateOR(IR::Value* x, IR::Value* y) {
    Instruction* instruction = new ORInstruction(x, y);
    Insert(instruction);

    return instruction;
}

void IRBuilder::Insert(Instruction* instruction) {
    Block->AppendInstruction(instruction);
}

}}} // end namespace