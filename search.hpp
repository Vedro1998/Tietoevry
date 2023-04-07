#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include <vector>
#include "structs.hpp"

void search(std::string search_dir, std::string pattern, 
            std::vector<search_res>* results);

#endif
