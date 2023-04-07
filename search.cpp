#include "search.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>

using namespace std;
namespace fs = filesystem;

void search_file(string filepath, string pattern, vector<search_res>* results){
    ifstream ifs(filepath);
    if(!ifs){
        cerr << "Search error: couldn't open file: " << filepath << endl;
    }
    else{
        int patterns_cnt = 0;
        vector<unsigned long> lines_with_pattern;
        string line;
        int line_idx = 0;
        while(!ifs.eof()){
            getline(ifs, line);
            regex reg(pattern);
            auto beg = sregex_iterator(line.begin(), line.end(), reg);
            auto end = sregex_iterator();
            int matches = distance(beg, end);
            if(matches > 0){
                patterns_cnt += matches;
                lines_with_pattern.push_back(line_idx);
            }
            line_idx++;
        }
        ifs.close();
        if(patterns_cnt > 0){
            search_res res {fs::absolute(filepath), patterns_cnt, lines_with_pattern};
            results->push_back(res);
        }
            
    }
}

// TODO: change name to 'grep' after changing conception
void search(string search_dir, string pattern, vector<search_res>* results){
    for(const auto& entry : fs::directory_iterator(search_dir)){
        if(entry.is_directory())
            search(entry.path(), pattern, results);
        else{
            //TODO: change to adding search_file() to thread pool
            //      +otoczyć muteksem aktualizację wektora wyników
            search_file(entry.path(), pattern, results);
        }
    }

}