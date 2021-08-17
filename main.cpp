//
//  main.cpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 13.08.2021.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <thread>

struct countLines
{
    int blankLines = 0;
    int commentLines = 0;
    int codeLines = 0;
    int totalLines = 0;
    
    countLines operator+ ( const countLines& obj )
    {
        blankLines   += obj.blankLines;
        commentLines += obj.commentLines;
        codeLines    += obj.codeLines;
        totalLines   += obj.totalLines;
        
        return *this;
    }
    
};

void checkCodeLine( const std::string &line, int& codeLines )
{
    std::size_t pos = line.find("//");
    
    std::string temp = line.substr(0, pos);
    std::string::iterator end_pos = std::remove(temp.begin(), temp.end(), ' ');
    temp.erase(end_pos, temp.end());
    
    if (temp.length() > 0)
    {
        codeLines++;
    }
}

void longCommentLine( std::ifstream &myfile, std::string line, int &commentLines, int &codeLines )
{
    commentLines++;
    checkCodeLine(line, codeLines);

    while ( line.find("*/") == std::string::npos )
    {
        commentLines++;
        getline(myfile,line);
    }
}

void shorCommentLine( std::ifstream &myfile, std::string line, int &commentLines, int &codeLines )
{
    checkCodeLine(line, codeLines);
    
    commentLines++;
}

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
        if (line.size() == 0)
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
        value.totalLines++;
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

void getAllFiles( std::vector<std::string> &allFiles, const std::string path )
{
    std::string fileName;
    const std::vector<std::string> proceedFiles { ".cpp", ".hpp", ".c", ".h" };
    
    for (const auto & entry : std::__fs::filesystem::directory_iterator(path))
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

int workWithGroupFiles ( countLines& value, const std::vector<std::string> files )
{
    int filesCounter = 0;
    
    std::string temp;
    
    for (std::vector<std::string>::const_iterator i = files.begin(); i != files.end(); ++i)
    {
        temp = *i;
        workWithFile(value, temp);
    }
    
    return filesCounter;
}

void getDirectoryStatistic( std::string path )
{
    std::vector<std::string> allFiles;

    countLines totalValue;
    countLines tempValue_1;
    countLines tempValue_2;

    
    getAllFiles( allFiles, path );
    
    std::vector<std::string> v_1(allFiles.begin(), allFiles.begin() + allFiles.size()/2),
                   v_2(allFiles.begin() + allFiles.size()/2, allFiles.end());
    
    int totalFiles = (int)allFiles.size();
    allFiles.clear();
    
    
    
    std::thread t1 (workWithGroupFiles, std::ref(tempValue_1), v_1);
    std::thread t2 (workWithGroupFiles, std::ref(tempValue_2), v_2);
    
    t1.join();
    t2.join();
    
    totalValue = tempValue_1 + tempValue_2;
    
    saveIntoFile(totalValue, totalFiles);
    
    std::cout << "--------------------------------------"      << std::endl;
    std::cout << "READED FILES: "  << totalFiles               << std::endl;
    std::cout << "BLANK LINES: "   << totalValue.blankLines    << std::endl;
    std::cout << "COMMENT LINES: " << totalValue.commentLines  << std::endl;
    std::cout << "CODE LINES: "    << totalValue.codeLines     << std::endl;
    std::cout << "TOTAL LINES: "   << totalValue.totalLines    << std::endl;
    std::cout << "--------------------------------------"      << std::endl;

}

int main ()
{
    
    const std::string path = "/Users/lamens/Library/Developer/Xcode/DerivedData/Task_3_by_Koval_Pavlo-dkwmyvnyemovydecmoabmqjfmqyh/Build/Products/Debug";
    
    getDirectoryStatistic(path);
    
    
    return 0;
}

