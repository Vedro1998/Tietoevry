#include <chrono>
#include "ArgParser.hpp"
#include "OutPrinter.hpp"
#include "errorcodes.hpp"
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


    grep_resources resources;
    auto start = chrono::high_resolution_clock::now();
    {
        GreprThreadPool pool(input.threads);
        search(input.dir, input.pattern, &resources, &pool);
    }

    sort_results(&(resources.results));
    sort_logs(&(resources.logs));
    
    OutPrinter op(resources.results, resources.logs);
    op.print_results(input.resultfile);
    op.print_logs(input.logfile);
    auto stop = chrono::high_resolution_clock::now();
    op.print_stats(input, (stop-start)/std::chrono::milliseconds(1));

}