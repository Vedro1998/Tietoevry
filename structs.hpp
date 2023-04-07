#ifndef STRUCTS_HPP
#define STRUCTS_HPP

#include <string>
#include <vector>

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

#endif