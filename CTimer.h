//
//  CTimer.h
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 18.08.2021.
//

#ifndef CTimer_h
#define CTimer_h

#include <chrono>
#include <iostream>

class CTimer
{
public:
    
    CTimer()
    {
        start = std::chrono::system_clock::now();
    }
    
    ~CTimer()
    {
        end = std::chrono::system_clock::now();
        std::chrono::duration<double> time = end - start;
        
        std::cout << "DURATION: " << time.count() << std::endl;
    }
private:
    
    std::chrono::time_point<std::chrono::system_clock> start, end;
};

#endif /* CTimer_h */
