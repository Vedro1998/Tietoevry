#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <utility>
#include "structs.hpp"

void print_results(std::string res_file, std::vector<search_res>* results);
void print_logs(std::string res_file, std::vector< std::pair<std::thread::id, std::vector<std::string>> >* threads_files);

#endif