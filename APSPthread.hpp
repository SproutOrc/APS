//
//  APSPthread.hpp
//  Lambda
//
//  Created by Atropos on 15/10/4.
//  Copyright © 2015年 Atropos. All rights reserved.
//

#ifndef APSPthread_HPP
#define APSPthread_HPP

#include <pthread.h>
#include <unistd.h>

#include <functional>

using std::function;

class APSPthread {
public:
    enum { LOOP = true };
    
public:
    APSPthread();
    APSPthread(function<void()> &task);
    ~APSPthread();
    
    void init(function<void()> &task);
    bool start(bool loop = false);
    void stop();
    
public:
    bool running();
    bool finished();

private:
    void pthreadTask();
    static void * cpp2cTask (void *ptr);
    
private:
    void setrunning(bool state);
    
private:
    function<void()> _task;
    pthread_t _pthread;
    
private:
    bool _isLoop;
    volatile bool _running;
    volatile bool _finished;
};
#endif /* APSPthread_HPP */
