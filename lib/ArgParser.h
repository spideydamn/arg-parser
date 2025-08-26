#pragma once

#include <string>
#include <vector>
#include <map>
#include <utility>
#include <set>
#include <cstring>
#include <string_view>
#include <sstream>

#include "Argument.h"

namespace ArgumentParser {
class ArgParser {
public:
    explicit ArgParser(const std::string& _name);

    bool Parse(const std::vector<std::string>& args);

    bool Parse(int argc, char **argv);


    bool ParseLongArg(const std::string_view& arg, size_t arg_len);

    bool ParseShortArg(const std::string_view& arg, size_t arg_len);

    bool ParsePositionalArg(const std::string_view& arg, size_t arg_len);


    bool MinArgsCountCheck();


    Argument::StringArgument& AddStringArgument(const char* long_arg);

    Argument::StringArgument& AddStringArgument(char short_arg, const char* long_arg);

    Argument::StringArgument& AddStringArgument(const char* long_arg, const char* help);

    Argument::StringArgument& AddStringArgument(char short_arg, const char* long_arg, const char* help);


    std::string GetStringValue(const char* arg);

    std::string GetStringValue(const char* arg, int num);

    std::string GetStringValue(char arg);

    std::string GetStringValue(char arg, int num);


    Argument::IntArgument& AddIntArgument(const char* long_arg);

    Argument::IntArgument& AddIntArgument(char short_arg, const char* long_arg);

    Argument::IntArgument& AddIntArgument(const char* long_arg, const char* help);

    Argument::IntArgument& AddIntArgument(char short_arg, const char* long_arg, const char* help);


    int GetIntValue(const char* arg);

    int GetIntValue(const char* arg, int num);


    int GetIntValue(char arg);

    int GetIntValue(char arg, int num);


    Argument::FlagArgument& AddFlag(const char* long_arg);

    Argument::FlagArgument& AddFlag(char short_arg, const char* long_arg);

    Argument::FlagArgument& AddFlag(const char* long_arg, const char* help);

    Argument::FlagArgument& AddFlag(char short_arg, const char* long_arg, const char* help);


    void Clear();


    bool GetFlag(const char* arg);

    bool GetFlag(const char* arg, int num);

    bool GetFlag(char arg);

    bool GetFlag(char arg, int num);


    void AddHelp(char _short_help, const char* _long_help, const char* _help_description);

    bool Help() const;

    bool HasShortHelp() const;

    bool HasLongHelp() const;

    char GetShortHelp() const;

    std::string GetLongHelp();

    std::string HelpDescription();

private:
    std::string name_{};

    std::map<std::string, Argument::IntArgument*> int_arguments_by_name_;
    std::map<std::string, Argument::StringArgument*> string_arguments_by_name_;
    std::map<std::string, Argument::FlagArgument*> flag_arguments_by_name_;

    bool has_help_ = false;
    char short_help_{};
    std::string long_help_{};

    bool has_short_help_{};
    bool has_long_help_{};

    std::string help_description_{};

    Argument::IntArgument* int_positional_argument_ = nullptr;
    Argument::StringArgument* string_positional_argument_ = nullptr;
    Argument::FlagArgument* flag_positional_argument_ = nullptr;
};
}
