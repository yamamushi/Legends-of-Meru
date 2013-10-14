#pragma once
//
//  ConcurrentQueue.h
//  Legends of Meru
//
//  Created by Jonathan Rumion on 10/13/13.
//  Copyright (c) 2013 The ASCII Project. All rights reserved.
//


#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>

template<typename Data>
class ConcurrentQueue
{
private:
    std::queue<Data> queue;
    mutable std::mutex mutx;
    std::condition_variable the_condition_variable;
public:
    void push(Data const& data)
    {
        std::lock_guard<std::mutex> lock(mutx);
        queue.push(data);
        the_condition_variable.notify_one();
    }
    
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(mutx);
        return queue.empty();
    }
    
    bool try_pop(Data& popped_value)
    {
        std::lock_guard<std::mutex> lock(mutx);
        if(queue.empty())
        {
            return false;
        }
        
        popped_value=queue.front();
        queue.pop();
        return true;
    }
    
    void wait_and_pop(Data& popped_value)
    {
        std::unique_lock<std::mutex> lock(mutx);
        while(queue.empty())
        {
            the_condition_variable.wait(lock);
        }
        
        popped_value=queue.front();
        queue.pop();
    }
    
};

