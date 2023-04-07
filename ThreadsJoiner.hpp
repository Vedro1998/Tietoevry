#ifndef THREADS_JOINER_HPP
#define THREADS_JOINER_HPP

#include <vector>
#include <thread>

class ThreadsJoiner {
public:
    explicit ThreadsJoiner(std::vector<std::thread>& threads_):
        threads(threads_)
    {}
    ~ThreadsJoiner(){
        for(unsigned long i=0;i<threads.size();++i){
            if(threads[i].joinable())
            threads[i].join();
        }
    }
private:
    std::vector<std::thread>& threads;
};

#endif