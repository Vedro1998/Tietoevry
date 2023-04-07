#ifndef GREPR_THREADPOOL_HPP
#define GREPR_THREADPOOL_HPP

#include <atomic>
#include <thread>
#include <functional>
#include <vector>
#include <string>
#include <mutex>
#include <utility>
#include "ThreadSafeQueue.hpp"
#include "ThreadsJoiner.hpp"
#include "structs.hpp"

class GreprThreadPool {
public:
    GreprThreadPool(unsigned thread_cnt) :
        done(false), joiner(threads), thread_cnt(thread_cnt)
    {
        try {
            for(unsigned i = 0; i < thread_cnt; i++)    
                threads.push_back(std::thread(&GreprThreadPool::worker_thread,this));
        }
        catch(...){
            done = true;
            throw;
        }
    }

    ~GreprThreadPool(){
        done = true;
    }

    template<typename FunctionType>
    void submit(FunctionType fun, std::string filepath, std::string pattern, grep_resources* resources)
    {
        work_queue.push(std::bind(fun, filepath, pattern, resources));
    }
private:
    std::atomic_bool done;
    ThreadSafeQueue<std::function<void()>> work_queue;
    std::vector<std::thread> threads;
    ThreadsJoiner joiner;
    unsigned thread_cnt;

    void worker_thread(){
        while(!done){
            std::function<void()> task;
            if(work_queue.try_pop(task))
                task();
            else 
                std::this_thread::yield();
        }
    }
};

#endif 