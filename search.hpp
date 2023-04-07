#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include <vector>
#include <utility>
#include <thread>
#include "structs.hpp"

void search(std::string search_dir, std::string pattern, 
            std::vector<search_res>* results, unsigned threads,
            std::vector< std::pair<std::thread::id, std::vector<std::string>> >* threads_files);

#endif
