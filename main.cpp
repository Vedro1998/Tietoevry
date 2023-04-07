#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <thread>
#include <utility>
#include <chrono>
#include <mutex>
#include "ArgParser.hpp"
#include "OutPrinter.hpp"
#include "errorcodes.hpp"
#include "types.hpp"
#include "structs.hpp"
#include "search.hpp"
#include "utils.hpp"

using namespace std;
using namespace std::chrono_literals;

int main(int argc, char* argv[]){
    ArgParser ap;
    grep_input input;
    int err = ap.parse(argc, argv, &input);
    if(err != NO_ERROR)
        return err;


    grep_res results;
    grep_logs logs;
    mutex results_mutex;
    mutex logs_mutex;
    auto start = chrono::high_resolution_clock::now();
    {
        GreprThreadPool pool(input.threads);
        search(input.dir, input.pattern, &results, &logs, &pool, &results_mutex, &logs_mutex);
    }

    sort_results(&results);
    sort_logs(&logs);
    
    OutPrinter op(results, logs);
    op.print_results(input.resultfile);
    op.print_logs(input.logfile);
    auto stop = chrono::high_resolution_clock::now();
    op.print_stats(input, (stop-start)/std::chrono::milliseconds(1));

}