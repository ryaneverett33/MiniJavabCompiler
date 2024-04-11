#include <ostream>
#include <map>
#include <string>

namespace MiniJavab {
namespace Core {
namespace IR {
class Value;
class PrinterImpl;

class ValuePrinter {
    public:
        static PrinterImpl Initialize();
        static PrinterImpl Get();
        void Print(std::ostream& out, const Value* value);
        void PrintNoType(std::ostream& out, const Value* value);
    private:
        PrinterImpl createImpl();
        void implWasDestroyed();

        std::unordered_map<const Value*, std::string> _valueMap;
        size_t _temporaryCount = 0;

        static inline uint32_t _instanceCount = 0;
        static inline ValuePrinter* _instance = nullptr;

        friend class PrinterImpl;
};

}}} // end namespace