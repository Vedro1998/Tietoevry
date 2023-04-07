#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <utility>

struct grep_input {
    std::string dir = "./";
    std::string logfile;
    std::string resultfile;
    std::string pattern;
    unsigned threads = 4;

};

struct info {
    int searched_files;
    int patterns_number;
    std::string result_file;
    std::string log_file;
    int used_threads;
    double elapsed_time;
};

struct search_res {
    std::string abs_filepath;
    int patterns_found;
    std::vector<unsigned long> pattern_lines;
    
};

using grep_results = std::vector<search_res>;
using grep_logs = std::vector< std::pair<std::thread::id, std::vector<std::string>> >;

struct grep_resources {
    grep_results results;
    grep_logs logs;
    std::mutex results_mutex;
    std::mutex logs_mutex;
};

#endif