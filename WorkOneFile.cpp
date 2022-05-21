//
//  WorkOneFile.cpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 18.08.2021.
//

#include "WorkOneFile.hpp"


void workWithFile( countLines& value, const std::string &fileName )
{
    std::string line;
    std::ifstream myfile;
    
    myfile.open(fileName);
    
    if (!myfile.is_open())
    {
        std::cout << "Unable to open file";
        exit(-1);
    }

    while ( getline (myfile,line) )
    {
        value.totalLines++;

        if (line.empty())
        {
            value.blankLines++;
            
        }else if (line.find("/*") != std::string::npos)
        {
            longCommentLine(myfile, line, value.commentLines, value.codeLines);
            
        } else if (line.find("//") != std::string::npos)
        {
            shorCommentLine(myfile, line, value.commentLines, value.codeLines);
            
        } else
        {
            value.codeLines++;
            
        }
    }
    
    myfile.close();
}

void saveIntoFile ( const countLines &value, const int filesCounter )
{
    std::ofstream myfile;
    myfile.open ("output.txt");
    
    if (!myfile.is_open())
    {
        std::cout << "Unable to open file";
        exit(-1);
    }
    
    myfile  << "READED FILES: "  << filesCounter        << std::endl;
    myfile  << "BLANK LINES: "   << value.blankLines    << std::endl;
    myfile  << "COMMENT LINES: " << value.commentLines  << std::endl;
    myfile  << "CODE LINES: "    << value.codeLines     << std::endl;
    myfile  << "TOTAL LINES: "   << value.totalLines    << std::endl;
    
    myfile.close();
}
