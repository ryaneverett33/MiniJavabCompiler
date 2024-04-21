#include <ostream>
#include <map>
#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {
class Value;
class PrinterImpl;

/// Implements shared stateful printing for IR::Value objects. Implements an RAII-esque interface to share
/// state across multiple "printer methods". Printer methods may use the ValuePrinter interface to print an
/// IR::Value object as a reference-able temporary (ex: %1) or named value (ex: %foo).
class ValuePrinter {
    public:
        /// Initializes a new shared state and returns a printer object for use. Any existing valid state
        /// is overwritten with this call
        /// @return The new printer object
        static PrinterImpl Initialize();

        /// Gets the printer object for the currently initialized state. If no state exists, then a new
        /// one will be created similarly to Initialize().
        /// @return The printer object
        static PrinterImpl Get();
    private:
        /// Prints a Value
        /// @see PrinterImpl::Print()
        void Print(std::ostream& out, const Value* value);

        /// Prints a Value without typing information
        /// @see PrinterImpl::PrintNoType()
        void PrintNoType(std::ostream& out, const Value* value);

        /// Creates a new printer object with the shared state and updates tracking information
        /// @return A new printer initialized with the shared instance
        PrinterImpl createImpl();

        /// Callback to indicate that a printer object was destroyed and updates tracking information.
        /// If all printer instances have been destroyed, the shared state instance will also be destroyed.
        /// @note This is called by printer objects during object destruction
        void implWasDestroyed();

        /// Helper function for getting the printable name of an IR::Value object
        /// @param value The object to get a name for
        /// @return The name or temporary id to print for the IR::Value object
        std::string getName(const Value* value);

        /// A mapping of known Value objects to their naming information. Values with known names, see 
        /// Value::HasName(), will have their actual name recorded, see Value::GetName(). Values without
        /// a known name will be a assigned a temporary name
        std::unordered_map<const Value*, std::string> _valueMap;

        /// Number of un-named temporaries within _valueMap. Used to name new temporaries.
        size_t _temporaryCount = 0;

        /// Number of printer objects that exist.
        static inline uint32_t _instanceCount = 0;

        /// The shared state object
        static inline ValuePrinter* _instance = nullptr;

        /// PrinterImpl has friendship so that it may access the destruction callback and the printer methods
        friend class PrinterImpl;
};

}}} // end namespace