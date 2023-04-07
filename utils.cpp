#include "utils.hpp"
#include <algorithm>

void sort_results(grep_res* results){
    sort(results->begin(), results->end(), [](search_res& r1, search_res& r2){
         return r2.patterns_found < r1.patterns_found; 
        });
}

void sort_logs(grep_logs* logs){
    sort(logs->begin(), logs->end(), [](auto& p1, auto& p2){
        return p2.second.size() <p1.second.size();
    });
}