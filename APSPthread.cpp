//
//  APSPthread.cpp
//  Lambda
//
//  Created by Atropos on 15/10/4.
//  Copyright © 2015年 Atropos. All rights reserved.
//

#include "APSPthread.hpp"

APSPthread::APSPthread() {
    _running = false;
    _finished = false;
    _pthread = 0;
}

APSPthread::APSPthread(function<void()> &task) {
    _task = task;
    _running = false;
    _finished = false;
    _pthread = 0;
}

APSPthread::~APSPthread() {
    
}

void APSPthread::init(function<void()> &task) {
    _task = task;
}

bool APSPthread::start(bool loop) {
    _isLoop = loop;
    
    if (_pthread != 0) {
        return false;
    }
    
    if (!_task) {
        return false;
    }
    
    int ret = pthread_create(&_pthread, nullptr, cpp2cTask, this);
    if (ret == 0) {
        return true;
    } else {
        return false;
    }
}

void APSPthread::stop() {
    pthread_cancel(_pthread);
    _finished = true;
}

bool APSPthread::running() {
    return _running;
}

void APSPthread::setrunning(bool state) {
    _running = state;
    _finished = state ? false : true;
}

void APSPthread::pthreadTask() {
    setrunning(true);
    if (_isLoop) {
        while (true) {
            _task();
            pthread_testcancel();
        }
    } else {
        _task();
    }
    setrunning(false);
}

void * APSPthread::cpp2cTask (void *ptr) {
    APSPthread * func  = (APSPthread *)ptr;
    func->pthreadTask();
    pthread_detach(pthread_self());
    return nullptr;
}

