#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <thread>
#include <utility>
#include <chrono>
#include <mutex>
#include "structs.hpp"
#include "search.hpp"
#include "print.hpp"

using namespace std;;

void print_help(){
    cout << "Usage: grepr <pattern (a string)> [-d | --dir <directory>]" << endl;
    cout << "       [-l | --log_file <logfile-path>] [-r | --result_file <result-file>]" << endl;
    cout << "       [-t | --threads <threads-in-threadpool>]" << endl;
}

bool is_param(char* arg, string param){
    string given = string(arg);
    string arg_long = string("--")+param;
    string arg_short = string("-")+param[0];
    return given==arg_short || given==arg_long;
}

bool value_given(int i, int argc){
    return i+1 < argc;
}

int main(int argc, char* argv[]){
    string dir = "./";
    string logfile = string(argv[0]) + ".log";
    string resultfile = string(argv[0]) + ".txt";
    string pattern;
    unsigned threads = 4;
    if(argc < 2 || is_param(argv[1], "help")){
        print_help();
        return 1;
    }
    
    pattern = string(argv[1]);
    for(int i = 2; i < argc; i++){
        if(is_param(argv[i], "dir") && value_given(i, argc))
            dir = string(argv[++i]);
        else if(is_param(argv[i], "log_file") && value_given(i, argc))
            logfile = string(argv[++i]);
        else if(is_param(argv[i], "result_file") && value_given(i, argc))
            resultfile = string(argv[++i]);
        else if(is_param(argv[i], "threads") && value_given(i, argc)){
            string arg = string(argv[++i]);
            istringstream formatter(arg);
            formatter >> threads;
        }
        else {
            cerr << "Invalid option: " << argv[i] << endl;
            print_help();
            return 2;
        }
    }


    vector<search_res> results;
    vector< pair<thread::id, vector<string>> > logs;
    mutex results_mutex;
    mutex logs_mutex;
    search(dir, pattern, &results, threads, &logs);
    {
        GreprThreadPool pool(threads);
        search(dir, pattern, &results, &logs, &pool, &results_mutex, &logs_mutex);
    }
    print_results(resultfile, &results);
    print_logs(logfile, &logs);

}