#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <thread>
#include <utility>
#include <chrono>
#include <mutex>
#include "ArgParser.hpp"
#include "errorcodes.hpp"
#include "structs.hpp"
#include "search.hpp"
#include "print.hpp"

using namespace std;
using namespace std::chrono_literals;



int main(int argc, char* argv[]){
    ArgParser ap;
    grep_input input;
    int err = ap.parse(argc, argv, &input);
    if(err != NO_ERROR)
        return err;


    vector<search_res> results;
    vector< pair<thread::id, vector<string>> > logs;
    mutex results_mutex;
    mutex logs_mutex;
    auto start = chrono::high_resolution_clock::now();
    {
        GreprThreadPool pool(input.threads);
        search(input.dir, input.pattern, &results, &logs, &pool, &results_mutex, &logs_mutex);
    }
    print_results(input.resultfile, &results);
    print_logs(input.logfile, &logs);
    auto stop = chrono::high_resolution_clock::now();
    auto time = stop-start;

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
    cout << "Elapsed time = " << time/std::chrono::milliseconds(1) << " [ms]" << endl;


}