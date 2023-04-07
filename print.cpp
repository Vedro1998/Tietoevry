#include "print.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

void print_results(string res_file, vector<search_res>* results){
    ofstream ofs(res_file);
    ifstream ifs;
    if(!ofs){
        cerr << "Error: couldn't open results file " << res_file;
        cerr << " for write" << endl;
    }
    else {
        sort(results->begin(), results->end(), [](search_res& r1, search_res& r2){ return r2.patterns_found < r1.patterns_found; });
        for(auto& res : *results){
            ifs.open(res.abs_filepath);
            if(!ifs){
                cerr << "Warning: couldn't open file " << res.abs_filepath << "for read" << endl;
                continue;
            }
            else {
                int line_idx = 0;
                int line_with_pattern_idx = 0;
                string line_buf;
                while(!ifs.eof()){
                    getline(ifs, line_buf);
                    // TODO: zmienić idx line_with_pattern_idx na iterator 
                    if(line_idx == res.pattern_lines[line_with_pattern_idx]){
                        ofs << res.abs_filepath << ":" << res.pattern_lines[line_with_pattern_idx] << ": " << line_buf << endl;
                        line_with_pattern_idx++;
                    }
                    line_idx++;
                }
                ifs.close();
            }
        }
        ofs.close();
    }
}

void print_logs(std::string log_file, vector< pair<thread::id, vector<string>> >* threads_files){
    sort(threads_files->begin(), threads_files->end(), [](auto& p1, auto& p2){return p2.second.size() <p1.second.size();});
    ofstream ofs(log_file);
    if(!ofs){
        cerr << "Error: unable to open log file: " << log_file << endl;
    }
    else {
        for(const auto& l: *threads_files){
            ofs << l.first << ": ";
            for(int i = 0; i < l.second.size(); i++){
                ofs << l.second[i].substr(l.second[i].find_last_of('/')+1);
                if(i < l.second.size()-1)
                    ofs << ", ";
                else
                    ofs << "\n";
            }
        }
        ofs.close();
    }

}
