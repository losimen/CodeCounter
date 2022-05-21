//
//  WorkGroupFile.cpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 18.08.2021.
//

#include "WorkGroupFile.hpp"

#include <thread>



void getAllFiles( std::vector<std::string> &allFiles, const std::string path )
{
    std::string fileName;
    const std::vector<std::string> proceedFiles { ".cpp", ".hpp", ".c", ".h" };
    
    for (const auto& entry : std::__fs::filesystem::recursive_directory_iterator(path))
    {
        fileName = entry.path();

            if ( fileName.rfind(".") != std::string::npos)
            {
                std::string fileType = fileName.substr(fileName.rfind("."));

                if ( std::find(proceedFiles.begin(), proceedFiles.end(), fileType) != proceedFiles.end() )
                    allFiles.push_back(fileName);
            }
    }
}

void workWithGroupFiles ( countLines& value, const std::vector<std::string> files )
{
    std::string temp;
    
    for (std::vector<std::string>::const_iterator i = files.begin(); i != files.end(); ++i)
    {
        temp = *i;
        workWithFile(value, temp);
    }
}

void getDirectoryStatistic( std::string path )
{
    const int amountOfThreds = 1;
    
    countLines totalValue;
    countLines tempValue[amountOfThreds];
    
    std::vector<std::string> allFiles;
    std::vector<std::string> groupFiles[amountOfThreds];
    
    getAllFiles( allFiles, path );
    
    
    int totalFiles = (int)allFiles.size();
    std::vector<std::vector<std::string>> temp = SplitVector(allFiles, amountOfThreds);
    
    for (int i = 0; i < amountOfThreds; i++)
    {
        groupFiles[i] = temp[i];
    }
    
    
    std::thread t[amountOfThreds];
    for (int i = 0; i < amountOfThreds; i++)
    {
        t[i] = std::thread(workWithGroupFiles, std::ref(tempValue[i]), std::ref(groupFiles[i]));
    }
    
    for (int i = 0; i < amountOfThreds; i++)
    {
        t[i].join();
    }
    
    for (int i = 0; i < amountOfThreds; i++)
    {
        totalValue = tempValue[i] + totalValue;
    }
    
    saveIntoFile(totalValue, totalFiles);
    
    std::cout << "--------------------------------------"      << std::endl;
    std::cout << "READED FILES: "  << totalFiles               << std::endl;
    std::cout << "BLANK LINES: "   << totalValue.blankLines    << std::endl;
    std::cout << "COMMENT LINES: " << totalValue.commentLines  << std::endl;
    std::cout << "CODE LINES: "    << totalValue.codeLines     << std::endl;
    std::cout << "TOTAL LINES: "   << totalValue.totalLines    << std::endl;
    std::cout << "--------------------------------------"      << std::endl;

}
