#ifndef OUT_PRINTER_HPP
#define OUT_PRINTER_HPP

#include <string>
#include <vector>
#include <fstream>
#include "structs.hpp"

class OutPrinter {
public:
    OutPrinter(const grep_results& results_, const grep_logs& logs_);
    void print_results(std::string res_file);
    void print_logs(std::string log_file);
    void print_stats( const grep_input& input, int time_ms);
private:
    void res_to_file(const search_res& res, std::ofstream& ofs);
    int count_searched_files();
    int count_patterns_found();
    const grep_logs& logs;
    const grep_results& results;
};

#endif