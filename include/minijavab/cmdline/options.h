#pragma once
#include <string>
#include <optional>
#include <any>
#include <map>
#include <vector>

namespace MiniJavab {
namespace Cmdline {

class Options;

/// Base class representing a command line flag
class FlagOption {
    public:
        /// Construct a FlagOption that expects an additional argument
        /// @param longOption The long form of the option, EX: --help
        /// @param shortOption The optional short form of the option, EX: -h
        FlagOption(std::string longOption, std::optional<std::string> shortOption = std::nullopt);

        /// Parse the string representation of the option value
        /// @param value The value to parse
        /// @return The parsed/typecasted version of the option
        virtual std::any Parse(std::string value);

        /// Wrapper function for setting the help message
        /// @param help The new help message
        /// @return This FlagOption object
        FlagOption* AddHelpMessage(std::string help) {
            HelpMessage = help;
            return this;
        }

        /// Wrapper function for setting the MaxOccurrences value
        /// @param occurrences The new MaxOccurrences value
        /// @return This FlagOption object
        FlagOption* AddMaxOccurrences(uint32_t occurrences) {
            MaxOccurrences = occurrences;
            return this;
        }

        /// @brief Wrapper function for denoting this option as required
        /// @return This FlagOption object 
        FlagOption* AddRequired() {
            Required = true;
            return this;
        }

        /// Resolve the flag name to the destination variable that will be stored in the results
        /// @return The name to store in the results table
        std::string ResolveDestinationVariable() const;

        /// A descriptive help message to print for this option
        std::optional<std::string> HelpMessage = std::nullopt;
        
        /// The name this variable will be stored as in the results map. By default, the
        /// destination variable is the same as the longOption.
        std::string DestinationVariable;

        /// The max number of times this command can appear
        uint32_t MaxOccurrences = 0;

        /// Whether or not this option is required to be supplied
        bool Required = false;
    protected:
        /// Whether or not this option expects an additional argument to follow
        /// @return True if the parser should parse another value, false otherwise
        virtual bool hasArgument() const { return true; }

    private:
        /// The shortened form of this option, optional
        /// EX: -h for --help
        std::string _shortOption;

        /// The long form of this option, required
        /// EX: --help
        std::string _longOption;

        /// Whether or not there exists a shortened form of the option
        bool _hasShortOption = false;

        friend class Options;
};

/// A command line flag that doesn't accept another argument and whose value is `true` on existence
class BoolFlagOption : public FlagOption {
    public:
        /// Construct a BoolFlagOption that doesn't accept an additional argument
        /// @param longOption The long form of the option, EX: --help
        /// @param shortOption The optional short form of the option, EX: -h
        BoolFlagOption(std::string longOption, std::optional<std::string> shortOption = std::nullopt)
            : FlagOption(longOption, shortOption) {
                MaxOccurrences = 1;
            }
    private:
        virtual bool hasArgument() const override { return false; }
};

/// A positional command line option
class PositionalOption {
    public:
        /// Construct a PositionalOption with a given name
        /// @param name Friendly name of the option to use in the results table and the help print
        PositionalOption(std::string name)
            : Name(name) {}

        /// Wrapper function for setting the help message
        /// @param help The new help message
        /// @return This PositionalOption object
        PositionalOption* AddHelpMessage(std::string help) {
            HelpMessage = help;
            return this;
        }

        /// Wrapper function for setting the MaxOccurrences value
        /// @param occurrences The new MaxOccurrences value
        /// @return This PositionalOption object
        PositionalOption* AddMaxOccurrences(uint32_t occurrences) {
            MaxOccurrences = occurrences;
            return this;
        }

        /// @brief Wrapper function for denoting this option as required
        /// @return This PositionalOption object 
        PositionalOption* AddRequired() {
            Required = true;
            return this;
        }

        /// The name of the option
        std::string Name;

        /// A descriptive help message to print for this option
        std::optional<std::string> HelpMessage = std::nullopt;

        /// The max number of times this command can appear
        uint32_t MaxOccurrences = 0;

        /// Whether or not this option is required to be supplied
        bool Required = false;
};

/// Represents the completed parsing result with known flag values
struct Results {
    /// A mapping of flags and their values
    std::map<std::string, std::vector<std::any>> FlagResults;

    /// A mapping of positional arguments and their values
    std::map<std::string, std::vector<std::any>> PositionalResults;
};

class Options {
    public:
        Options(std::string toolName, std::optional<std::string> toolDescription);
        
        /// Print the help text and exit
        void PrintHelp(void) const;

        /// Print the usage text and exit
        void PrintUsage(void) const;

        /// Add a new command line flag definition
        /// @param option The command line flag to use in parsing
        /// @return The added command line flag for further customization
        FlagOption* AddFlagOption(FlagOption* option);

        /// Add a new positional argument definition
        /// @param option The positional argument for use in parsing
        /// @return The added positional argument for further customization
        PositionalOption* AddPositionalArgument(PositionalOption* option);

        /// Parse the arguments given to the application
        /// @note @a argc and @a argv should be the same values from `int main()`
        /// @param argc The number of arguments
        /// @param argv The array of arguments
        /// @return A results table filled in with parsing data
        Results Parse(int argc, char** argv) const;

        /// The name of the tool for help and usage messages
        std::string ToolName;

        /// A description of the tool for help and usage messages
        std::optional<std::string> ToolDescription;
    private:
        /// Looks up a registered flag definition
        /// @param flag The name of the flag to lookup
        /// @param isShortOption Whether or not this is a short flag or long flag
        /// @return The flag definition if it was found, else nullptr
        FlagOption* lookupFlag(std::string flag, bool isShortOption) const;

        /// A list of all registered command line flags
        std::vector<FlagOption*> _flags;

        /// A list of all registered positional arguments
        std::vector<PositionalOption*> _positionals; 
};

}} // end namespace