#include "search.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include "GreprThreadPool.hpp"

#include <thread>

using namespace std;
namespace fs = filesystem;

void update_logs(string filepath, grep_resources* resources){
    thread::id id = this_thread::get_id();
    resources->logs_mutex.lock();
    auto found_it = find_if(resources->logs.begin(), resources->logs.end(), [=](auto& l){return l.first==id;});
    if(found_it != resources->logs.end())
            found_it->second.push_back(filepath);        
        else
            resources->logs.emplace_back(id, vector<string>{filepath});
    resources->logs_mutex.unlock();
}

void update_results(int patterns_cnt, string filepath, grep_resources* resources,
                    const vector<unsigned long>& lines_with_pattern)
{
    if(patterns_cnt > 0){
        search_res res {fs::absolute(filepath), patterns_cnt, lines_with_pattern};
        resources->results_mutex.lock();
        resources->results.push_back(res);
        resources->results_mutex.unlock();
    }
}

void search_file(string filepath, string pattern, grep_resources* resources)
{
    update_logs(filepath, resources);
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
        update_results(patterns_cnt, filepath, resources, lines_with_pattern);
    }
}

void search(string search_dir, string pattern, grep_resources* resources,
            GreprThreadPool* pool)
{
    for(const auto& entry : fs::directory_iterator(search_dir)){
        if(entry.is_directory())
            search(entry.path(), pattern, resources, pool);
        else
            pool->submit(search_file, entry.path(), pattern, resources);
    }

}