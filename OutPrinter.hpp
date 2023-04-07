#ifndef OUT_PRINTER_HPP
#define OUT_PRINTER_HPP

#include <string>
#include <vector>
#include "structs.hpp"
#include "types.hpp"

class OutPrinter {
public:
    void print_results(std::string res_file, grep_res* results);
    void print_logs(std::string log_file, grep_logs* logs);
    void print_stats(const grep_logs& logs, const grep_res& results, int time_ms, const grep_input& input);
};

#endif