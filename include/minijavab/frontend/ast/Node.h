#pragma once
#include <vector>
#include <iostream>

namespace MiniJavab {
namespace Frontend {
namespace AST {

class Node {
    public:
        virtual void Str(std::ostream& out) = 0;
        virtual void Dump(std::ostream& out) {
            Str(out);
            out << std::endl;
        }
        void Dump() {
            Dump(std::cout);
        }
        std::ostream &operator<<(std::ostream &os) { 
            Dump(os);
            return os;
        }
};

}}} // end namespace