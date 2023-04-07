#include "ArgParser.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include "errorcodes.hpp"

using namespace std;

int ArgParser::parse(int argc, char* argv[], grep_input* input){
    if(argc < 2 || is_param(argv[1], "help")){
        print_help();
        return ARG_NUM_ERROR;
    }

    input->logfile = string(argv[0]) + ".log";
    input->resultfile = string(argv[0]) + ".txt";

    input->pattern = string(argv[1]);
    for(int i = 2; i < argc; i++){
        if(is_param(argv[i], "dir") && value_given(i, argc))
            input->dir = string(argv[++i]);
        else if(is_param(argv[i], "log_file") && value_given(i, argc))
            input->logfile = string(argv[++i]);
        else if(is_param(argv[i], "result_file") && value_given(i, argc))
            input->resultfile = string(argv[++i]);
        else if(is_param(argv[i], "threads") && value_given(i, argc)){
            string arg = string(argv[++i]);
            istringstream formatter(arg);
            formatter >> input->threads;
        }
        else {
            cerr << "Invalid option: " << argv[i] << endl;
            print_help();
            return ARG_INVALID_ERROR;
        }
    }

    return NO_ERROR;
}

void ArgParser::print_help(){
    cout << "Usage: grepr <pattern (a string)> [-d | --dir <directory>]" << endl;
    cout << "       [-l | --log_file <logfile-path>] [-r | --result_file <result-file>]" << endl;
    cout << "       [-t | --threads <threads-in-threadpool>]" << endl;
}

bool ArgParser::is_param(char* arg, string param){
    string given = string(arg);
    string arg_long = string("--")+param;
    string arg_short = string("-")+param[0];
    return given==arg_short || given==arg_long;  
}

bool ArgParser::value_given(int i, int argc){
    return i+1 < argc;
}