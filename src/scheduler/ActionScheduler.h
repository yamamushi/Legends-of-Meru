#pragma once
//
//  ActionScheduler.h
//  Legends of Meru
//
//  Created by Jonathan Rumion on 10/13/13.
//  Copyright (c) 2013 The ASCII Project. All rights reserved.
//


#include "ConcurrentQueue.h"

class ActionScheduler {
    
private:
    
    ConcurrentQueue<int> queue;
    
public:
    
    void write(int x){queue.push(x);};
    int read_next(){ int x; queue.wait_and_pop(x); return x;};
    bool is_empty(){return queue.empty();};
    
};



