#include <iostream>
#include <filesystem>

#include "minijavab/frontend/frontend.h"

#include "minijavab/core/ir/Module.h"

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

std::vector<std::filesystem::path> resolveInputs(Cmdline::Results& results) {
    std::vector<std::filesystem::path> inputs;

    // Resolve any command line arguments
    for (std::any input : results.PositionalResults["inputs"]) {
        std::string file = std::any_cast<std::string>(input);
        if (!std::filesystem::exists(file)) {
            std::cerr << "Input file doesn't exist: '" << file << "'!\n";
            return {};
        }
        inputs.push_back(file);
    }
    return inputs;
}

int main(int argc, char** argv) {
    Cmdline::Options parser = constructArgumentParser();
    Cmdline::Results results = parser.Parse(argc, argv);

    std::vector<std::filesystem::path> inputs = resolveInputs(results);
    if (inputs.empty()) { return 1; }

    Core::IR::Module* mod = Frontend::LoadProgramFile(inputs[0]);
    if (mod == nullptr) {
        exit(2);
    }
    mod->Dump();

    return 0;
}