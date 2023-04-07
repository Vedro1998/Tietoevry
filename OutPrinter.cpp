#include "OutPrinter.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

void OutPrinter::print_results(string res_file, grep_res* results){
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

void OutPrinter::print_logs(string log_file, grep_logs* logs){
    sort(logs->begin(), logs->end(), [](auto& p1, auto& p2){return p2.second.size() <p1.second.size();});
    ofstream ofs(log_file);
    if(!ofs){
        cerr << "Error: unable to open log file: " << log_file << endl;
    }
    else {
        for(const auto& l: *logs){
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

void OutPrinter::print_stats(const grep_logs& logs, const grep_res& results, int time_ms, const grep_input& input){
    int searched_files = 0;
    for(const auto& l: logs){
        searched_files += l.second.size();
    }

    int patterns_number = 0;
    for(const auto& res: results){
        patterns_number += res.patterns_found;
    }
    cout << "Searched files: " << searched_files << endl;
    cout << "Files with pattern: " << results.size() << endl;
    cout << "Patterns number: " << patterns_number << endl;
    cout << "Result file: " << input.resultfile << endl;
    cout << "Log file: " << input.logfile << endl;
    cout << "Used threads: " << logs.size() << endl;
    cout << "Elapsed time = " << time_ms << " [ms]" << endl;
}