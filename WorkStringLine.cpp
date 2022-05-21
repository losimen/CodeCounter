//
//  WorkStringLine.cpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 19.08.2021.
//

#include "WorkStringLine.hpp"

std::vector<std::vector<std::string>> SplitVector( const std::vector<std::string>& vec, size_t n )
{
    std::vector<std::vector<std::string>> outVec;

    size_t length = vec.size() / n;
    size_t remain = vec.size() % n;

    size_t begin = 0;
    size_t end = 0;

    for (size_t i = 0; i < std::min(n, vec.size()); ++i)
    {
        end += (remain > 0) ? (length + !!(remain--)) : length;

        outVec.push_back(std::vector<std::string>(vec.begin() + begin, vec.begin() + end));

        begin = end;
    }

    return outVec;
}

void checkCodeLine( const std::string &line, int& codeLines , const std::string &comment )
{
    std::size_t pos = line.find(comment);
    
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
    checkCodeLine(line, codeLines, "/*");

    while ( line.find("*/") == std::string::npos )
    {
        commentLines++;
        getline(myfile,line);
    }
}

void shorCommentLine( std::ifstream &myfile, const std::string& line, int &commentLines, int &codeLines )
{
    checkCodeLine(line, codeLines, "//");
    
    commentLines++;
}
