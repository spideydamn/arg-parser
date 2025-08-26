#include "Argument.h"

namespace Argument {
IntArgument::IntArgument(char short_name, const std::string& long_name, const std::string& help) {
    if (short_name != -1) {
        has_short_name_ = true;
        short_name_ = short_name;
    }
    if (!long_name.empty()) {
        has_long_name_ = true;
        long_name_ = long_name;
    }
    if (!help.empty()) {
        has_help_ = true;
        help_ = help;
    }
}

int IntArgument::GetValue() const {
    return (*storage_)[0];
}

int IntArgument::GetValue(int num) const {
    return (*storage_)[num];
}

void IntArgument::PutValue(int new_value) {
    if (is_multi_value_) {
        storage_->push_back(new_value);
        ++size_;
    } else {
        *first_storage_ = new_value;
        size_ = 1;
    }
}

void IntArgument::StoreValue(int& storage) {
    first_storage_ = &storage;
}

void IntArgument::StoreValues(std::vector<int>& storage) {
    storage_ = &storage;
}

IntArgument& IntArgument::Default(int default_value) {
    *first_storage_ = default_value;
    has_default_ = true;
    default_ = default_value;
    size_ = 1;
    return *this;
}

IntArgument& IntArgument::MultiValue() {
    is_multi_value_ = true;
    return *this;
}

IntArgument& IntArgument::MultiValue(size_t min_args_count) {
    is_multi_value_ = true;
    min_args_count_ = min_args_count;
    return *this;
}

IntArgument& IntArgument::Positional() {
    is_positional_ = true;
    return *this;
}

bool IntArgument::IsPositional() const {
    return is_positional_;
}

size_t IntArgument::GetSize() const {
    return size_;
}

size_t IntArgument::GetMinArgsCount() const {
    return min_args_count_;
}

char IntArgument::GetShortName() const {
    return short_name_;
}

std::string IntArgument::GetLongName() const {
    return long_name_;
}

std::string IntArgument::GetHelp() const {
    return help_;
}

bool IntArgument::HasShortName() const {
    return has_short_name_;
}

bool IntArgument::HasLongName() const {
    return has_long_name_;
}

bool IntArgument::HasHelp() const {
    return has_help_;
}

bool IntArgument::HasDefault() const {
    return has_default_;
}

bool IntArgument::IsMultiValue() const {
    return is_multi_value_;
}

int IntArgument::GetDefault() const {
    return default_;
}

void IntArgument::PutInfo(std::stringstream& string_stream) const {
    if (this->HasShortName()) {
        string_stream << "-";
        string_stream << this->GetShortName();
        if (this->HasLongName() || this->HasHelp() || this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasLongName()) {
        string_stream << ("--" + this->GetLongName() + "=<int>");
        if (this->HasHelp() || this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasHelp()) {
        string_stream << (this->GetHelp());
        if (this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
        string_stream << '[';
        if (this->HasDefault()) {
            string_stream << "default = ";
            string_stream << this->GetDefault();
            if (this->IsMultiValue() || this->IsPositional()) {
                string_stream << ", ";
            }
        }
        if (this->IsMultiValue()) {
            string_stream << "repeated, min args = ";
            string_stream << this->GetMinArgsCount();
            if (this->IsPositional()) {
                string_stream << ", ";
            }
        }
        if (this->IsPositional()) {
            string_stream << "positional";
        }
        string_stream << ']';
    }
    string_stream << '\n';
};




StringArgument::StringArgument(char short_name, const std::string& long_name, const std::string& help) {
    if (short_name != -1) {
        has_short_name_ = true;
        short_name_ = short_name;
    }
    if (!long_name.empty()) {
        has_long_name_ = true;
        long_name_ = long_name;
    }
    if (!help.empty()) {
        has_help_ = true;
        help_ = help;
    }
}

std::string StringArgument::GetValue() const {
    return (*storage_)[0];
}

std::string StringArgument::GetValue(int num) const {
    return (*storage_)[num];
}

void StringArgument::PutValue(const std::string& new_value) {
    if (is_multi_value_) {
        storage_->emplace_back(new_value);
        ++size_;
    } else {
        *first_storage_ = new_value;
        size_ = 1;
    }
}

void StringArgument::StoreValue(std::string& storage) {
    first_storage_ = &storage;
}

void StringArgument::StoreValues(std::vector<std::string>& storage) {
    storage_ = &storage;
}

StringArgument& StringArgument::Default(const char* default_value) {
    *first_storage_ = default_value;
    has_default_ = true;
    default_ = default_value;
    size_ = 1;
    return *this;
}

StringArgument& StringArgument::MultiValue() {
    is_multi_value_ = true;
    return *this;
}

StringArgument& StringArgument::MultiValue(size_t min_args_count) {
    is_multi_value_ = true;
    min_args_count_ = min_args_count;
    return *this;
}

StringArgument& StringArgument::Positional() {
    is_positional_ = true;
    return *this;
}

bool StringArgument::IsPositional() const {
    return is_positional_;
}

size_t StringArgument::GetSize() const {
    return size_;
}

size_t StringArgument::GetMinArgsCount() const {
    return min_args_count_;
}

char StringArgument::GetShortName() const {
    return short_name_;
}

std::string StringArgument::GetLongName() const {
    return long_name_;
}

std::string StringArgument::GetHelp() const {
    return help_;
}

bool StringArgument::HasShortName() const {
    return has_short_name_;
}

bool StringArgument::HasLongName() const {
    return has_long_name_;
}

bool StringArgument::HasHelp() const {
    return has_help_;
}

bool StringArgument::HasDefault() const {
    return has_default_;
}

bool StringArgument::IsMultiValue() const {
    return is_multi_value_;
}

std::string StringArgument::GetDefault() const {
    return default_;
}

void StringArgument::PutInfo(std::stringstream& string_stream) const {
    if (this->HasShortName()) {
        string_stream << "-";
        string_stream << this->GetShortName();
        if (this->HasLongName() || this->HasHelp() || this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasLongName()) {
        string_stream << ("--" + this->GetLongName());
        string_stream << "=<string>";
        if (this->HasHelp() || this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasHelp()) {
        string_stream << (this->GetHelp());
        if (this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
        string_stream << '[';
        if (this->HasDefault()) {
            string_stream << "default = ";
            string_stream << this->GetDefault();
            if (this->IsMultiValue() || this->IsPositional()) {
                string_stream << ", ";
            }
        }
        if (this->IsMultiValue()) {
            string_stream << "repeated, min args = ";
            string_stream << this->GetMinArgsCount();
            if (this->IsPositional()) {
                string_stream << ", ";
            }
        }
        if (this->IsPositional()) {
            string_stream << "positional";
        }
        string_stream << ']';
    }
    string_stream << '\n';
}



FlagArgument::FlagArgument(char short_name, const std::string& long_name, const std::string& help) {
    if (short_name != -1) {
        has_short_name_ = true;
        short_name_ = short_name;
    }
    if (!long_name.empty()) {
        has_long_name_ = true;
        long_name_ = long_name;
    }
    if (!help.empty()) {
        has_help_ = true;
        help_ = help;
    }
}

bool FlagArgument::GetValue() const {
    return (*storage_)[0];
}

bool FlagArgument::GetValue(int num) const {
    return (*storage_)[num];
}

void FlagArgument::PutValue(bool new_value) {
    if (is_multi_value_) {
        storage_->push_back(new_value);
        ++size_;
    } else {
        *first_storage_ = new_value;
        (*storage_)[0] = new_value;
        size_ = 1;
    }
}

void FlagArgument::StoreValue(bool& storage) {
    first_storage_ = &storage;
}

void FlagArgument::StoreValues(std::deque<bool>& storage) {
    storage_ = &storage;
}

FlagArgument& FlagArgument::Default(bool default_value) {
    (*storage_)[0] = default_value;
    has_default_ = true;
    default_ = default_value;
    size_ = 1;
    return *this;
}

FlagArgument& FlagArgument::MultiValue() {
    is_multi_value_ = true;
    return *this;
}

FlagArgument& FlagArgument::MultiValue(size_t min_args_count) {
    is_multi_value_ = true;
    min_args_count_ = min_args_count;
    return *this;
}

FlagArgument& FlagArgument::Positional() {
    is_positional_ = true;
    return *this;
}

bool FlagArgument::IsPositional() const {
    return is_positional_;
}

size_t FlagArgument::GetSize() const {
    return size_;
}

size_t FlagArgument::GetMinArgsCount() const {
    return min_args_count_;
}

char FlagArgument::GetShortName() const {
    return short_name_;
}

std::string FlagArgument::GetLongName() const {
    return long_name_;
}

std::string FlagArgument::GetHelp() const {
    return help_;
}

bool FlagArgument::HasShortName() const {
    return has_short_name_;
}

bool FlagArgument::HasLongName() const {
    return has_long_name_;
}

bool FlagArgument::HasHelp() const {
    return has_help_;
}

bool FlagArgument::HasDefault() const {
    return has_default_;
}

bool FlagArgument::IsMultiValue() const {
    return is_multi_value_;
}

bool FlagArgument::GetDefault() const {
    return default_;
}

void FlagArgument::PutInfo(std::stringstream& string_stream) const {
    if (this->HasShortName()) {
        string_stream << "-";
        string_stream << this->GetShortName();
        if (this->HasLongName() || this->HasHelp() || this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasLongName()) {
        string_stream << ("--" + this->GetLongName());
        if (this->HasHelp() || this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasHelp()) {
        string_stream << (this->GetHelp());
        if (this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
            string_stream << ", ";
        }
    }
    if (this->HasDefault() || this->IsMultiValue() || this->IsPositional()) {
        string_stream << '[';
        if (this->HasDefault()) {
            string_stream << "default = ";
            if (this->GetDefault()) {
                string_stream << "true";
            } else {
                string_stream << "false";
            }
            if (this->IsMultiValue() || this->IsPositional()) {
                string_stream << ", ";
            }
        }
        if (this->IsMultiValue()) {
            string_stream << "repeated, min args = ";
            string_stream << this->GetMinArgsCount();
            if (this->IsPositional()) {
                string_stream << ", ";
            }
        }
        if (this->IsPositional()) {
            string_stream << "positional";
        }
        string_stream << ']';
    }
    string_stream << '\n';
}
}
