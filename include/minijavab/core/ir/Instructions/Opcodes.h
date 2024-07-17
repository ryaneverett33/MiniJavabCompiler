#pragma once

#include <string>
#include <cassert>

namespace MiniJavab {
namespace Core {
namespace IR {

enum class Opcode {
    UNKNOWN,
    // Control Flow Instructions

    /// Return without value
    Ret,
    /// Return with a value
    RetValue,
    /// Return with an immediate
    RetImmediate,
    /// Branch to a location without control flow return or parameters passed
    Br,
    /// Branch to a location with control flow and parameters passed
    Call,
    /// Branch to a location based on a previous comparison
    BrIf,
    // Binary Operations

    /// Add two values together
    AddValueValue,
    /// Add a value and an immediate
    AddValueImmediate,
    /// Subtract a value from a value
    SubValueValue,
    /// Subtract an immediate from a value
    SubValueImmediate,
    /// Multiply a value by another value
    MulValueValue,
    /// Multiple a value by an immediate
    MulValueImmediate,
    /// Divide a value by another value
    DivValueValue,
    /// Divide a value by an immediate
    DivValueImmediate,
    /// Boolean OR a value and another value
    OrValueValue,
    /// Boolean OR a value and an immediate
    OrValueImmediate,
    /// Boolean AND a value and another value
    AndValueValue,
    /// Boolean AND a value and an immediate
    AndValueImmediate,
    /// XOR Instruction with a value and another value
    XORValueValue,
    /// XOR Instruction with a value and an immediate
    XORValueImmediate,

    // Memory operations

    /// Allocate a local (function-scoped) variable
    Alloc,
    /// Load from a local variable
    Load,
    /// Store a value into memory
    Store,
    /// Get a pointer to a value
    GetPtrValue,
    /// Get a pointer with an immediate value
    GetPtrImmediate,
    /// Compare a value with another value
    CmpValueValue,
    /// Compare a value with an immediate
    CmpValueImmediate
};

// todo: don't inline this
inline std::string GetInstructionName(const Opcode opcode) {
    switch (opcode) {
        case Opcode::Ret:
        case Opcode::RetImmediate:
        case Opcode::RetValue:
            return "ret";
        case Opcode::Alloc:
            return "alloc";
        case Opcode::Store:
            return "store";
        case Opcode::Load:
            return "load";
        case Opcode::GetPtrImmediate:
        case Opcode::GetPtrValue:
            return "getptr";
        case Opcode::Call:
            return "call";
        case Opcode::MulValueImmediate:
        case Opcode::MulValueValue:
            return "mul";
        case Opcode::XORValueImmediate:
        case Opcode::XORValueValue:
            return "xor";
        case Opcode::AddValueImmediate:
        case Opcode::AddValueValue:
            return "add";
        case Opcode::SubValueImmediate:
        case Opcode::SubValueValue:
            return "sub";
        case Opcode::DivValueImmediate:
        case Opcode::DivValueValue:
            return "div";
        case Opcode::Br:
            return "br";
        case Opcode::BrIf:
            return "br_if";
        case Opcode::CmpValueImmediate:
        case Opcode::CmpValueValue:
            return "cmp";
        case Opcode::AndValueImmediate:
        case Opcode::AndValueValue:
            return "and";
        case Opcode::OrValueImmediate:
        case Opcode::OrValueValue:
            return "or";
        default:
            assert(false && "Instruction not added yet!");
    }
}

}}} // end namespace