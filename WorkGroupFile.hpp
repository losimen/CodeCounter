//
//  WorkGroupFile.hpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 18.08.2021.
//

#ifndef WorkGroupFile_hpp
#define WorkGroupFile_hpp

#include "WorkOneFile.hpp"

void getAllFiles( std::vector<std::string> &allFiles, std::string path );

void workWithGroupFiles ( countLines& value, std::vector<std::string> files );

void getDirectoryStatistic( std::string path );


#endif /* WorkGroupFile_hpp */
