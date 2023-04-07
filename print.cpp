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
                    // TODO: pomyśleć, czy nie zmienić na ignore, dopóki idx się nie zgadza
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