#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <utility>
#include <thread>
#include <string>
#include "structs.hpp"

using grep_results = std::vector<search_res>;
using grep_logs = std::vector< std::pair<std::thread::id, std::vector<std::string>> >;

#endif