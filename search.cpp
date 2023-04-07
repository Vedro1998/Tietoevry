#include "search.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <mutex>
#include <unordered_map>
#include "GreprThreadPool.hpp"

#include <thread>

using namespace std;
namespace fs = filesystem;

void search_file(string filepath, string pattern, vector<search_res>* results, 
                 mutex* results_mutex, vector< pair<thread::id, vector<string>> >* logs, mutex* logs_mutex)
{
    thread::id id = this_thread::get_id();
    logs_mutex->lock();
    auto found_it = find_if(logs->begin(), logs->end(), [=](auto& l){return l.first==id;});
    if(found_it != logs->end())
            found_it->second.push_back(filepath);        
        else
            logs->emplace_back(id, vector<string>{filepath});
    logs_mutex->unlock();

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
            results_mutex->lock();
            results->push_back(res);
            results_mutex->unlock();
        }
            
    }
}

void search(string search_dir, string pattern, vector<search_res>* results, unsigned threads, 
            vector< pair<thread::id, vector<string>> >* threads_files){
    GreprThreadPool pool(threads);
    mutex results_mutex;
    mutex logs_mutex;
    for(const auto& entry : fs::directory_iterator(search_dir)){
        if(entry.is_directory())
            search(entry.path(), pattern, results, threads, threads_files);
        else{
            pool.submit(search_file, entry.path(), pattern, results, &results_mutex, threads_files, &logs_mutex);
        }
    }

}