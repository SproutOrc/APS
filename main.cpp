//
//  main.cpp
//  Lambda
//
//  Created by Atropos on 15/9/2.
//  Copyright © 2015年 Atropos. All rights reserved.
//

#include <iostream>
#include <string>

#include "APSPthread.hpp"

int main(int argc, const char * argv[]) {
    
    function<void()> task = [](){
        printf("hello world! \n");
        sleep(1);
    };
    
    APSPthread th(task);
    
    th.start();
    
    pause();
    return 0;
}
