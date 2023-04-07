#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <string>
#include <vector>
#include "GreprThreadPool.hpp"
#include "structs.hpp"

void search(std::string search_dir, std::string pattern, grep_resources* resources,
            GreprThreadPool* pool);

#endif
