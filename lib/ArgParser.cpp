#include "ArgParser.h"

namespace ArgumentParser {
ArgParser::ArgParser(const std::string& name) {
    name_ = name;
}

bool ArgParser::Parse(const std::vector<std::string>& args) {
    size_t argc = args.size();
    char* argv[args.size()];
    for (int i = 0; i < argc; ++i) {
        argv[i] = new char[args[i].length() + 1];
        strcpy(argv[i], args[i].c_str());
    }
    return this->Parse(static_cast<int>(argc), argv);
}

bool ArgParser::Parse(int argc, char **argv) {
    std::string_view arg;
    int equal_pos;
    for (int i = 1; i < argc; ++i) {
        arg = argv[i];
        size_t arg_len = arg.length();
        if (arg_len > 2 && arg.substr(2) == GetLongHelp() || arg_len == 2 && (arg[1] == GetShortHelp())) {
            has_help_ = true;
            continue;
        }
        if (arg[0] == '-' && arg[1] == '-') {
            if (!this->ParseLongArg(arg, arg_len)) {
                return false;
            }
        } else if (arg[0] == '-') {
            if (!this->ParseShortArg(arg, arg_len)) {
                return false;
            }
        } else {
            if (!this->ParsePositionalArg(arg, arg_len)) {
                return false;
            }
        }
    }

    return this->MinArgsCountCheck();
}

bool ArgParser::ParseLongArg(const std::string_view& arg, size_t arg_len) {
    size_t equal_pos;
    for (equal_pos = 2; equal_pos < arg_len; ++equal_pos) {
        if (arg[equal_pos] == '=') {
            break;
        }
    }

    if (int_arguments_by_name_.find(std::string{arg.substr(2, equal_pos - 2)}) == int_arguments_by_name_.end() &&
        flag_arguments_by_name_.find(std::string{arg.substr(2, equal_pos - 2)}) == flag_arguments_by_name_.end() &&
        string_arguments_by_name_.find(std::string{arg.substr(2, equal_pos - 2)}) == string_arguments_by_name_.end()) {
        return false;
    }
    if (int_arguments_by_name_.find(std::string{arg.substr(2, equal_pos - 2)}) != int_arguments_by_name_.end()) {
        if (equal_pos == arg_len - 1 && arg[equal_pos] != '=') {
            return false;
        }
        int_arguments_by_name_[std::string{arg.substr(2, equal_pos - 2)}]->PutValue(std::stoi(std::string{arg.substr(equal_pos + 1)}));
    } else if (string_arguments_by_name_.find(std::string{arg.substr(2, equal_pos - 2)}) != string_arguments_by_name_.end()) {
        if (equal_pos == arg_len - 1 && arg[equal_pos] != '=') {
            return false;
        }
        string_arguments_by_name_[std::string{arg.substr(2, equal_pos - 2)}]->PutValue(std::string{arg.substr(equal_pos + 1)});
    } else if (flag_arguments_by_name_.find(std::string{arg.substr(2, equal_pos - 2)}) != flag_arguments_by_name_.end()) {
        flag_arguments_by_name_[std::string{arg.substr(2, equal_pos - 2)}]->PutValue(true);
    }
    return true;
}

bool ArgParser::ParseShortArg(const std::string_view& arg, size_t arg_len) {
    size_t equal_pos = 2;
    if (arg[equal_pos] != '=') {
        for (int j = 1; j < arg_len; ++j) {
            if (flag_arguments_by_name_.find(std::string{arg.substr(j, 1)}) == flag_arguments_by_name_.end()) {
                return false;
            }
            flag_arguments_by_name_[std::string{arg.substr(j, 1)}]->PutValue(true);
        }
        return true;
    }
    if (int_arguments_by_name_.find(std::string{arg.substr(1, 1)}) == int_arguments_by_name_.end() && string_arguments_by_name_.find(std::string{arg.substr(1, 1)}) == string_arguments_by_name_.end()) {
        return false;
    }
    if (equal_pos == arg_len - 1 && arg[equal_pos] != '=') {
        return false;
    }
    if (int_arguments_by_name_.find(std::string{arg.substr(1, 1)}) != int_arguments_by_name_.end()) {
        int_arguments_by_name_[std::string{arg.substr(1, equal_pos - 1)}]->PutValue(std::stoi(std::string{arg.substr(equal_pos + 1)}));
    } else if (string_arguments_by_name_.find(std::string{arg.substr(1, 1)}) != string_arguments_by_name_.end()){
        string_arguments_by_name_[std::string{arg.substr(1, equal_pos - 1)}]->PutValue(std::string{arg.substr(equal_pos + 1)});
    }
    return true;
}

bool ArgParser::ParsePositionalArg(const std::string_view& arg, size_t arg_len) {
    if (int_positional_argument_ == nullptr && string_positional_argument_ == nullptr &&
        flag_positional_argument_ == nullptr) {
        for (const auto& [_name, _arg] : int_arguments_by_name_) {
            if (_arg->IsPositional()) {
                int_positional_argument_ = _arg;
            }
        }
        for (const auto& [_name, _arg] : string_arguments_by_name_) {
            if (_arg->IsPositional()) {
                string_positional_argument_ = _arg;
            }
        }
        for (const auto& [_name, _arg] : flag_arguments_by_name_) {
            if (_arg->IsPositional()) {
                flag_positional_argument_ = _arg;
            }
        }
    }
    if (int_positional_argument_ == nullptr && string_positional_argument_ == nullptr &&
        flag_positional_argument_ == nullptr) {
        return false;
    }
    if (int_positional_argument_ != nullptr) {
        int_positional_argument_->PutValue(std::stoi(std::string{arg}));
    } else if (string_positional_argument_ != nullptr) {
        string_positional_argument_->PutValue(std::string{arg});
    } else {
        if (arg == "true" || arg == "1") {
            flag_positional_argument_->PutValue(true);
        } else if (arg == "false" || arg == "0") {
            flag_positional_argument_->PutValue(false);
        } else {
            return false;
        }
    }
    return true;
}

bool ArgParser::MinArgsCountCheck() {
    for (const auto& [_name, _arg] : int_arguments_by_name_) {
        if (_arg->GetSize() < _arg->GetMinArgsCount() && !has_help_) {
            return false;
        }
    }

    for (const auto& [_name, _arg] : string_arguments_by_name_) {
        if (_arg->GetSize() < _arg->GetMinArgsCount() && !has_help_) {
            return false;
        }
    }

    for (const auto& [_name, _arg] : flag_arguments_by_name_) {
        if (_arg->GetSize() < _arg->GetMinArgsCount() && !has_help_) {
            return false;
        }
    }

    return true;
}
    
Argument::StringArgument& ArgParser::AddStringArgument(const char* long_arg) {
    return this->AddStringArgument(-1, long_arg, "");
}

Argument::StringArgument& ArgParser::AddStringArgument(char short_arg, const char* long_arg) {
    return this->AddStringArgument(short_arg, long_arg, "");
}

Argument::StringArgument& ArgParser::AddStringArgument(const char *long_arg, const char *help) {
    return this->AddStringArgument(-1, long_arg, help);
}

Argument::StringArgument&
ArgParser::AddStringArgument(char short_arg, const char* long_arg, const char* help) {
    auto* new_arg = new Argument::StringArgument(short_arg, long_arg, help);
    std::string _short_arg(1, short_arg);
    string_arguments_by_name_[_short_arg] = new_arg;
    string_arguments_by_name_[long_arg] = new_arg;
    return *string_arguments_by_name_[_short_arg];
}

std::string ArgParser::GetStringValue(const char* arg) {
    return string_arguments_by_name_[arg]->GetValue();
}

std::string ArgParser::GetStringValue(const char* arg, int num) {
    return string_arguments_by_name_[arg]->GetValue(num);
}

std::string ArgParser::GetStringValue(char arg) {
    std::string _arg(1, arg);
    return string_arguments_by_name_[_arg]->GetValue();
}

std::string ArgParser::GetStringValue(char arg, int num) {
    std::string _arg(1, arg);
    return string_arguments_by_name_[_arg]->GetValue(num);
}


Argument::IntArgument& ArgParser::AddIntArgument(const char* long_arg) {
    return this->AddIntArgument(-1, long_arg, "");
}

Argument::IntArgument& ArgParser::AddIntArgument(char short_arg, const char* long_arg) {
    return this->AddIntArgument(short_arg, long_arg, "");
}

Argument::IntArgument &ArgParser::AddIntArgument(char short_arg, const char *long_arg, const char *help) {
    auto* new_arg = new Argument::IntArgument(short_arg, long_arg, help);
    std::string _short_arg(1, short_arg);
    int_arguments_by_name_[_short_arg] = new_arg;
    int_arguments_by_name_[long_arg] = new_arg;
    return *int_arguments_by_name_[_short_arg];
}

Argument::IntArgument& ArgParser::AddIntArgument(const char* long_arg, const char* help) {
    return this->AddIntArgument(-1, long_arg, help);
}

int ArgParser::GetIntValue(const char* arg) {
    return int_arguments_by_name_[arg]->GetValue();
}

int ArgParser::GetIntValue(const char* arg, int num) {
    return int_arguments_by_name_[arg]->GetValue(num);
}

int ArgParser::GetIntValue(char arg) {
    std::string _arg(1, arg);
    return int_arguments_by_name_[_arg]->GetValue();
}

int ArgParser::GetIntValue(char arg, int num) {
    std::string _arg(1, arg);
    return int_arguments_by_name_[_arg]->GetValue(num);
}

Argument::FlagArgument &ArgParser::AddFlag(const char* long_arg) {
    return this->AddFlag(-1, long_arg, "");
}

Argument::FlagArgument& ArgParser::AddFlag(char short_arg, const char* long_arg) {
    return this->AddFlag(short_arg, long_arg, "");
}

Argument::FlagArgument& ArgParser::AddFlag(const char* long_arg, const char* help) {
    return this->AddFlag(-1, long_arg, help);
}

Argument::FlagArgument& ArgParser::AddFlag(char short_arg, const char* long_arg, const char* help) {
    auto* new_arg = new Argument::FlagArgument(short_arg, long_arg, help);
    std::string _short_arg(1, short_arg);
    flag_arguments_by_name_[_short_arg] = new_arg;
    flag_arguments_by_name_[long_arg] = new_arg;
    return *flag_arguments_by_name_[_short_arg];
}

bool ArgParser::GetFlag(const char* arg) {
    return flag_arguments_by_name_[arg]->GetValue();
}

bool ArgParser::GetFlag(const char* arg, int num) {
    return flag_arguments_by_name_[arg]->GetValue(num);
}

bool ArgParser::GetFlag(char arg) {
    char* _arg = new char[1];
    _arg[0] = arg;
    return flag_arguments_by_name_[_arg]->GetValue();
}

bool ArgParser::GetFlag(char arg, int num) {
    char* _arg = new char[1];
    _arg[0] = arg;
    return flag_arguments_by_name_[_arg]->GetValue(num);
}

void ArgParser::Clear() {
    for (const auto& [_name, _arg] : int_arguments_by_name_) {
        delete _arg;
    }
    for (const auto& [_name, _arg] : string_arguments_by_name_) {
        delete _arg;
    }
    for (const auto& [_name, _arg] : flag_arguments_by_name_) {
        delete _arg;
    }
}

void ArgParser::AddHelp(char _short_help, const char* _long_help, const char* _help_description) {
    short_help_ = _short_help;
    has_short_help_ = true;
    long_help_ = _long_help;
    has_long_help_ = true;
    help_description_ = _help_description;
}

bool ArgParser::Help() const {
    return has_help_;
}

bool ArgParser::HasShortHelp() const {
    return has_short_help_;
}

bool ArgParser::HasLongHelp() const {
    return has_long_help_;
}

char ArgParser::GetShortHelp() const {
    return short_help_;
}

std::string ArgParser::GetLongHelp() {
    return long_help_;
}

std::string ArgParser::HelpDescription() {
    std::stringstream returned_help_description;
    returned_help_description << name_ << '\n';
    returned_help_description << help_description_ << "\n\n";

    std::set<Argument::IntArgument*> int_args;
    for (const auto& [_name, _arg] : int_arguments_by_name_) {
        int_args.insert(_arg);
    }
    for (auto* arg : int_args) {
        arg->PutInfo(returned_help_description);
    }

    std::set<Argument::StringArgument*> string_args;
    for (const auto& [_name, _arg] : string_arguments_by_name_) {
        string_args.insert(_arg);
    }
    for (auto* arg : string_args) {
        arg->PutInfo(returned_help_description);
    }

    std::set<Argument::FlagArgument*> flag_args;
    for (const auto& [_name, _arg] : flag_arguments_by_name_) {
        flag_args.insert(_arg);
    }
    for (auto* arg : flag_args) {
        arg->PutInfo(returned_help_description);
    }
    returned_help_description << '\n';
    if (Help()) {
        if (HasShortHelp()) {
            returned_help_description << '-' << GetShortHelp();
            if (HasLongHelp()) {
                returned_help_description << ", ";
            }
        }
        if (HasLongHelp()) {
            returned_help_description << "--" << GetLongHelp();
        }
        returned_help_description << "Display this help and exit\n";
    }
    return returned_help_description.str();
}
}
