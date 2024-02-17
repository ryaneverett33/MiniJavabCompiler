#pragma once
#include <string>
#include <map>
#include <vector>

#include "minijavab/core/ir/Value.h"

namespace MiniJavab {
namespace Core {
namespace IR {

/// Describes what kind of type the constant is
enum class ConstantKind {
    Integer,
    String,
    Struct,
    Vector,
    Pointer
};

/// Base class for describing a runtime-immutable constant value
class Constant : public Value {
    public:
        /// Get the kind of Constant this is
        /// @see ConstantKind
        /// @return The kind value
        ConstantKind GetKind() const { return _kind; }
        
        /// Print the textual representation of this constant to stderr
        /// @see Constant::Print()
        void Dump() const;

        /// Print the textual representation of this constant to the given stream.
        /// Useful for chaining multiple Print() calls into one
        /// @param out The stream to print to
        virtual void Print(std::ostream& out = std::cerr) const = 0;

        /// Creates a null constant for a given type
        /// @param type The constant type to create
        /// @return A new Constant object
        static Constant* GetNull(Type* type);
    protected:
        /// @param type The value type for this constant
        /// @param kind The kind of constant this is
        Constant(IR::Type* type, ConstantKind kind);
    
    private:
        /// The kind of constant this is, should be able to static_cast with this knowledge
        ConstantKind _kind;
};

}}} // end namespace