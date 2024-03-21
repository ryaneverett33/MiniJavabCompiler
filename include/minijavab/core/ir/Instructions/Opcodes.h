#pragma once

#include <string>
#include <cassert>

namespace MiniJavab {
namespace Core {
namespace IR {

enum class Opcode {
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

    // Memory operations

    /// Allocate a local (function-scoped) variable
    Alloc,
    /// Load from a local variable
    Load,
    /// Store a value into a local variable
    StoreValue,
    /// Store an immediate into a local variable
    StoreImmediate,
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
        default:
            assert(false && "Instruction not added yet!");
    }
}

}}} // end namespace