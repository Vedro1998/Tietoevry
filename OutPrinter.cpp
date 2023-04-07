#include "OutPrinter.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

OutPrinter::OutPrinter(const grep_results& results_, const grep_logs& logs_) :
            results(results_), logs(logs_)
{}

void OutPrinter::print_results(string res_file){
    ofstream ofs(res_file);
    if(!ofs){
        cerr << "Error: couldn't open results file " << res_file;
        cerr << " for write" << endl;
    }
    else {
        for(auto& res : results)
            res_to_file(res, ofs);
        ofs.close();
    }
}

void OutPrinter::res_to_file(const search_res& res, ofstream& ofs){
    ifstream ifs;
    ifs.open(res.abs_filepath);
    if(!ifs){
        cerr << "Warning: couldn't open file " << res.abs_filepath << "for read" << endl;
    }
    else {
        int line_idx = 0;
        auto line_it = res.pattern_lines.begin();
        string line_buf;
        while(!ifs.eof()){
            getline(ifs, line_buf);
            if(line_idx == *line_it){
                ofs << res.abs_filepath << ":" << line_idx << ": " << line_buf << endl;
                line_it++;
            }
            line_idx++;
        }
        ifs.close();
    }
}

void OutPrinter::print_logs(string log_file){
    ofstream ofs(log_file);
    if(!ofs){
        cerr << "Error: unable to open log file: " << log_file << endl;
    }
    else {
        for(const auto& l: logs){
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

void OutPrinter::print_stats(const grep_input& input, int time_ms){
    cout << "Searched files: " << count_searched_files() << endl;
    cout << "Files with pattern: " << results.size() << endl;
    cout << "Patterns number: " << count_patterns_found() << endl;
    cout << "Result file: " << input.resultfile << endl;
    cout << "Log file: " << input.logfile << endl;
    cout << "Used threads: " << logs.size() << endl;
    cout << "Elapsed time = " << time_ms << " [ms]" << endl;
}

int OutPrinter::count_searched_files(){
    int cnt = 0;
    for(const auto& l: logs)
        cnt += l.second.size();
    return cnt;
}

int OutPrinter::count_patterns_found(){
    int cnt = 0;
    for(const auto& res: results){
        cnt += res.patterns_found;
    }
    return cnt;
}