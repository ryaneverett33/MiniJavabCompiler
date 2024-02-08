#include "minijavab/cmdline/options.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace MiniJavab {
namespace Cmdline {

/// The amount of padding to use in the help message
constexpr size_t PADDING_LENGTH = 32;

FlagOption::FlagOption(std::string longOption, std::optional<std::string> shortOption)
    : _longOption(longOption) {
    if (shortOption != std::nullopt) {
        _shortOption = shortOption.value();
        _hasShortOption = true;
    }
}

std::any FlagOption::Parse(std::string value) {
    return value;
}

std::string FlagOption::ResolveDestinationVariable() const {
    // If the user has already set the DestinationVariable, just use that
    if (!DestinationVariable.empty()) {
        return DestinationVariable;
    }

    // Else calculate the DestinationVariable from the long option name by replacing any special
    // characters
    std::string destinationVariable = _longOption;
    std::transform(destinationVariable.begin(), destinationVariable.end(), destinationVariable.begin(),
        [](unsigned char c) -> unsigned char {
            if (c == '-') {
                return '_';
            }
            return c;
    });
   
    return destinationVariable;
}

Options::Options(std::string toolName, std::optional<std::string> toolDescription)
    : ToolName(toolName),
    ToolDescription(toolDescription) {}

void Options::PrintHelp(void) const {
    // Helper function for getting the padding needed for a flag
    auto getPadding = [](std::string shortOption, std::string longOption) -> std::string {
        size_t optionLength = 2 /* "--".length */ + longOption.length();
        if (shortOption.length() > 0) {
            optionLength += 1 /* "-".length */ + shortOption.length() + 1 /* ",".length */;
        }

        return std::string(PADDING_LENGTH - optionLength, ' ');
    };
    // Helper function for getting the padding needed for a positional option
    auto getPositionalPadding = [](std::string name) -> std::string {
        return std::string(PADDING_LENGTH - name.length(), ' ');
    };

    std::cout << ToolName;
    if (ToolDescription != std::nullopt) {
        std::cout << ": " << ToolDescription.value();
    }
    std::cout << "\n\n";
    
    std::cout << "Options:\n";
    std::cout << "-h,--help" << getPadding("h", "help") << "Displays this Help message\n";
    for (FlagOption* option : _flags) {
        if (option->_hasShortOption) {
            std::cout << "-" << option->_shortOption << ",";
        }
        std::cout << "--" << option->_longOption;
        if (option->HelpMessage != std::nullopt) {
            std::cout << getPadding(option->_shortOption, option->_longOption) << option->HelpMessage.value();
        }
        std::cout << "\n";
    }

    std::cout << "\nPositional Options:\n";
    for (PositionalOption* option : _positionals) {
        std::cout << option->Name;
        if (option->HelpMessage != std::nullopt) {
            std::cout << getPositionalPadding(option->Name) << option->HelpMessage.value();
        }
        std::cout << "\n";
    }
    exit(1);
}

void Options::PrintUsage(void) const {
    // TODO
    std::cout << "USAGE: " << ToolName << "\n";
    exit(1);
}

FlagOption* Options::AddFlagOption(FlagOption* option) {
    // Verify the option is valid
    if (option == nullptr) {
        throw std::invalid_argument("Option can't be null!");
    }

    // Verify the option doesn't already exist
    for (FlagOption* exisitingOption : _flags) {
        if (option->_longOption == exisitingOption->_longOption) {
            throw std::invalid_argument("Option already exists!");
        }
    }

    // Add the option to the list and return it
    _flags.push_back(option);
    return option;
}

PositionalOption* Options::AddPositionalArgument(PositionalOption* option) {
    // Verify the option is valid
    if (option == nullptr) {
        throw std::invalid_argument("Option can't be null!");
    }

    // Verify the option doesn't already exist
    for (PositionalOption* exisitingOption : _positionals) {
        if (option->Name == exisitingOption->Name) {
            throw std::invalid_argument("Option already exists!");
        }
    }

    // Add the option to the list and return it
    _positionals.push_back(option);
    return option;
}

FlagOption* Options::lookupFlag(std::string flag, bool isShortOption) const {
    // Iterate through the known flag options and find the matching option value
    for (FlagOption* option : _flags) {
        if (isShortOption && option->_hasShortOption &&
            option->_shortOption == flag) {
                return option;
        }
        else if (!isShortOption && option->_longOption == flag) {
            return option;
        }
    }
    return nullptr;
}

Results Options::Parse(int argc, char** argv) const {
    // Helper function for determining if a string is a flag
    // Flags are of the form `-blah` or `--blah`
    auto isFlag = [](std::string& s) -> bool {
        if (s.length() < 2) {
            return false;
        }
        else if (s.length() == 2) {
            return s[1] != '-';
        }
        else {
            return (s[0] == '-' && s[1] != '-') ||
                    (s[0] == '-' && s[1] == '-' && s[2] != '-');
        }
    };

    // Parsed results structure
    Results results;
    // Index into the _positionals table of the positional that's next to be parsed
    size_t positionalIndex = 0;
    // Amount of times the positional at positionalIndex has been parsed
    size_t positionalCount = 0;
    // A lookup table of all the positional names
    std::vector<std::string> positionalNames = std::vector<std::string>(_positionals.size());
    for (size_t i = 0; i < _positionals.size(); i++) {
        positionalNames[i] = _positionals[i]->Name;
    }

    // Iterate through the passed arguments (skipping the executable argument) and parse values
    int i = 1;
    for (; i < argc; i++) {
        std::string flagOrPositional = std::string(argv[i]);

        if (isFlag(flagOrPositional)) {
            // Figure out which flag it is
            bool isShortFlag = flagOrPositional[1] != '-';
            std::string flag = flagOrPositional.substr(isShortFlag ? 1 : 2);

            if (isShortFlag && flag == "h") {
                PrintHelp();
            }
            else if (!isShortFlag && flag == "help") {
                PrintHelp();
            }
            else {
                // Lookup flag definition
                FlagOption* option = lookupFlag(flag, isShortFlag);
                if (option == nullptr) {
                    std::cerr << "Unrecognized flag: " << flagOrPositional << "\n";
                    PrintUsage();
                }

                // Parse argument if the option expects an argument
                std::any argument;
                if (option->hasArgument()) {
                    if ((i + 1) >= argc) {
                        std::cerr << "Missing required value for " << flagOrPositional << "\n";
                        PrintUsage();
                    }
                    i += 1;
                    argument = option->Parse(std::string(argv[i]));
                }
                else {
                    // Currently only BooleanFlag doesn't expect an argument, so hackily handle that case
                    argument = true;
                }

                // Add the known flag vaulue to the results table
                std::string flagDestination = option->ResolveDestinationVariable();
                std::map<std::string, std::vector<std::any>>::iterator searchResult = results.FlagResults.find(flagDestination);
                if (searchResult != results.FlagResults.end()) {
                    // Check if the user has over specified a flag
                    if (option->MaxOccurrences != 0 && searchResult->second.size() == option->MaxOccurrences) {
                        std::cerr << "Flag --" << option->_longOption << " can only be specified " << option->MaxOccurrences << " times!\n";
                        PrintUsage(); 
                    }
                    searchResult->second.push_back(argument);
                }
                else {
                    results.FlagResults.insert(std::make_pair(flagDestination, std::vector<std::any>({argument})));
                }

            }
        }
        else {
            // Figure out which positional it is
            if (positionalIndex >= _positionals.size()) {
                std::cerr << "Invalid positional argument: " << flagOrPositional << "\n";
                PrintUsage();
            }

            // Get the next positional value to parse
            // TODO: handle the error case where there are no more positionals to parse
            PositionalOption* positional = _positionals[positionalIndex];
            if (results.PositionalResults.size() == positionalIndex) {
                results.PositionalResults.insert(std::make_pair(positionalNames[positionalIndex], std::vector<std::any>()));
            }

            // Record the positional value in the results table
            results.PositionalResults[positionalNames[positionalIndex]].push_back(flagOrPositional);
            positionalCount += 1;

            // Check for MaxOccurrences and increase the positionalIndex if MaxOccurrences has occurred 
            if (positional->MaxOccurrences != 0 && positionalCount == positional->MaxOccurrences) {
                positionalIndex += 1;
                positionalCount = 0;
            }
        }
    }

    // Verify required flags
    for (FlagOption* option : _flags) {
        if (option->Required && results.FlagResults.find(option->ResolveDestinationVariable()) == results.FlagResults.end()) {
            std::cerr << "Flag --" << option->_longOption << " is required!\n";
            PrintUsage();
        }
    }

    // Verify required positional arguments
    for (PositionalOption* option : _positionals) {
        if (option->Required && results.PositionalResults.find(option->Name) == results.PositionalResults.end()) {
            std::cerr << "Position argument " << option->Name << " is required!\n";
            PrintUsage();
        }
    }

    return results;
}

}} // end namespace