#include <iostream>

#include "minijavab/cmdline/options.h"
using namespace MiniJavab;

MiniJavab::Cmdline::Options constructArgumentParser() {
    using namespace MiniJavab::Cmdline;

    Options options("mjavabc", "The MiniJavab compiler. Compile MiniJavab source files to native code");
    options.AddPositionalArgument((new PositionalOption("inputs"))
                                    ->AddHelpMessage("The Input files to compile")
                                    ->AddRequired()
                                    ->AddMaxOccurrences(1));

    return options;
}

int main(int argc, char** argv) {
    Cmdline::Options parser = constructArgumentParser();
    Cmdline::Results results = parser.Parse(argc, argv);

    for (std::any input : results.PositionalResults["inputs"]) {
        std::string file = std::any_cast<std::string>(input);
        std::cout << file << "\n";
    }

    return 0;
}