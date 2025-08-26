#pragma once

#include <string>
#include <vector>
#include <deque>
#include <sstream>

namespace Argument {
class IntArgument {
public:
    IntArgument(char short_name=-1, const std::string& long_name="", const std::string& help="");


    int GetValue() const;

    int GetValue(int num) const;

    void PutValue(int new_value);


    void StoreValue(int& storage);

    void StoreValues(std::vector<int>& storage);


    IntArgument& Default(int default_value);


    IntArgument& MultiValue();

    IntArgument& MultiValue(size_t min_args_count);


    IntArgument& Positional();


    char GetShortName() const;

    std::string GetLongName() const;

    std::string GetHelp() const;


    size_t GetSize() const;

    size_t GetMinArgsCount() const;

    int GetDefault() const;


    bool HasShortName() const;

    bool HasLongName() const;

    bool HasHelp() const;

    bool HasDefault() const;


    bool IsMultiValue() const;

    bool IsPositional() const;

    void PutInfo(std::stringstream& stringstream) const;

private:
    char short_name_ = -1;
    std::string long_name_{};

    std::string help_{};

    std::vector<int> values_ = std::vector<int>(1, 0);

    int* first_storage_ = &values_[0];

    std::vector<int>* storage_ = &values_;

    size_t min_args_count_ = 1;

    size_t size_ = 0;

    int default_{};

    bool has_short_name_ = false;
    bool has_long_name_ = false;
    bool has_help_ = false;

    bool has_default_ = false;

    bool is_multi_value_ = false;

    bool is_positional_ = false;
};

class StringArgument {
public:
    StringArgument(char short_name=-1, const std::string& long_name="", const std::string& help="");

    std::string GetValue() const;

    std::string GetValue(int num) const;

    void PutValue(const std::string& new_value);


    void StoreValue(std::string& storage);

    void StoreValues(std::vector<std::string>& storage);


    StringArgument& Default(const char* default_value);


    StringArgument& MultiValue();

    StringArgument& MultiValue(size_t min_args_count);


    StringArgument& Positional();


    char GetShortName() const;

    std::string GetLongName() const;

    std::string GetHelp() const;


    size_t GetSize() const;

    size_t GetMinArgsCount() const;

    std::string GetDefault() const;


    bool HasShortName() const;

    bool HasLongName() const;

    bool HasHelp() const;

    bool HasDefault() const;


    bool IsMultiValue() const;

    bool IsPositional() const;

    void PutInfo(std::stringstream& stringstream) const;
private:
    char short_name_ = -1;
    std::string long_name_{};

    std::string help_{};

    std::vector<std::string> values_ = std::vector<std::string>(1, "");

    std::string* first_storage_ = &values_[0];

    std::vector<std::string>* storage_ = &values_;

    size_t min_args_count_ = 1;
    size_t size_ = 0;

    std::string default_{};

    bool has_short_name_ = false;
    bool has_long_name_ = false;
    bool has_help_ = false;

    bool has_default_ = false;

    bool is_multi_value_ = false;

    bool is_positional_ = false;
};

class FlagArgument {
public:
    FlagArgument(char short_name=-1, const std::string& long_name="", const std::string& help="");


    bool GetValue() const;

    bool GetValue(int num) const;

    void PutValue(bool new_value);


    void StoreValue(bool& storage);

    void StoreValues(std::deque<bool>& storage);


    FlagArgument& Default(bool default_value);


    FlagArgument& MultiValue();

    FlagArgument& MultiValue(size_t min_args_count);


    FlagArgument& Positional();


    char GetShortName() const;

    std::string GetLongName() const;

    std::string GetHelp() const;


    size_t GetSize() const;

    size_t GetMinArgsCount() const;

    bool GetDefault() const;


    bool HasShortName() const;

    bool HasLongName() const;

    bool HasHelp() const;

    bool HasDefault() const;


    bool IsMultiValue() const;

    bool IsPositional() const;

    void PutInfo(std::stringstream& stringstream) const;
private:
    char short_name_ = -1;
    std::string long_name_{};

    std::string help_{};

    std::deque<bool> values_ = std::deque<bool>(1, false);

    bool* first_storage_ = &values_[0];

    std::deque<bool>* storage_ = &values_;

    size_t min_args_count_ = 1;
    size_t size_ = 1;

    bool default_{};

    bool has_short_name_ = false;
    bool has_long_name_ = false;
    bool has_help_ = false;

    bool is_multi_value_ = false;

    bool is_positional_ = false;

    bool has_default_ = false;
};
}
