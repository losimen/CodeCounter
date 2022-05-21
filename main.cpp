//
//  main.cpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 13.08.2021.
//

#include "CTimer.h"
#include "WorkGroupFile.hpp"


int main ()
{
    CTimer timer;
    
    const std::string path = "/Users/lamens/Library/Developer/Xcode/DerivedData/Task_3_by_Koval_Pavlo-dkwmyvnyemovydecmoabmqjfmqyh/Build/Products/Debug";
    
    getDirectoryStatistic(path);
    
    return 0;
}


