//
//  WorkStringLine.hpp
//  Task 3 by Koval Pavlo
//
//  Created by Павло Коваль on 19.08.2021.
//

#ifndef WorkStringLine_hpp
#define WorkStringLine_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

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

std::vector<std::vector<std::string>> SplitVector( const std::vector<std::string>& vec, size_t n );

void checkCodeLine( const std::string &line, int& codeLines , const std::string &comment );

void longCommentLine( std::ifstream &myfile, std::string line, int &commentLines, int &codeLines );

void shorCommentLine( std::ifstream &myfile, const std::string& line, int &commentLines, int &codeLines );

#endif /* WorkStringLine_hpp */
