#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include <vector>
#include <utility>
#include <thread>
#include <mutex>
#include "GreprThreadPool.hpp"
#include "structs.hpp"

void search(std::string search_dir, std::string pattern, 
            std::vector<search_res>* results,
            std::vector< std::pair<std::thread::id, std::vector<std::string>> >* threads_files,
            GreprThreadPool* pool, std::mutex* results_mutex, std::mutex* logs_mutex);

#endif
