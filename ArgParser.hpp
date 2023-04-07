#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include "structs.hpp"

class ArgParser {
public:
    int parse(int argc, char* argv[], grep_input* input);
private:
    bool is_param(char* arg, std::string param);
    void print_help();
    bool value_given(int i, int argc);
};

#endif