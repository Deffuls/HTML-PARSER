#pragma once

#include "../signals/signals.h"
#include <string>
#include <sstream>
#include <vector>

namespace Format{
    
    void ReplaceString(std::string& subject, const std::string& search, const std::string& replace) {
        std::size_t pos = 0;
        while ( (pos = subject.find(search, pos) ) != std::string::npos) {
            subject.replace(pos, search.length(), replace);
            pos += replace.length();
        }
    }

    void StripString(std::string& subject, std::vector<char> trimVector){

        int lastPos = (int)(subject.size() - 1);

        char beginChar = subject[0];
        char endChar = subject[ lastPos ];

        if (beginChar == trimVector[0]){
            subject.erase(0);
        }
        else if (beginChar == trimVector[1]) { 
            subject.erase(0);
        }

        if (endChar == trimVector[0]) { 
            subject.erase(lastPos);
        }
        else if (endChar == trimVector[1])  { 
            subject.erase(lastPos);
        }
    }

    std::string CopyUntil(const std::string& subject, std::vector<char> stopChars ){

        std::string out;
        
        int index = 0;
        int finish = (int)subject.size();
        char strChar;

        bool bStop = false;

        while (index < finish)
        {
            strChar = subject[index];

            for (char stop : stopChars){
                if (stop == strChar){
                    bStop = true;
                    break;
                }
            }
            if (bStop) { break; }
            out += strChar;
            index++;
        }

        return out;
    }
    
    STATUS ShrinkString(std::string& subject, const std::string& begin, const std::string& end){
        std::size_t begin_pos = 0;
        std::size_t end_pos = 0;
        
        begin_pos = subject.find(begin, begin_pos);
        end_pos = subject.find(end, end_pos);
        
        if ( begin_pos == std::string::npos || end_pos == std::string::npos) { return STRING_NOT_FOUND; }
        
        std::size_t length = (end_pos - begin_pos) + end.size();
        subject = subject.substr(begin_pos, length);
        return SUCCESS;
    }
    
    std::vector<std::string> SplitString(std::string str, char delim, bool firstOccurence=false) {
        std::vector<std::string> tokens;
        
        std::size_t position = (std::size_t)0;
        std::size_t lastPos = (std::size_t)0;

        for (;;){
            position = str.find(delim, position);

            if (position == std::string::npos){
                position = (std::size_t)(str.size() - 1);
                std::string formatted = str.substr(lastPos + 1, position - 2 );
                tokens.push_back( formatted );
                break;
            }
            tokens.push_back(
                str.substr(lastPos, position)
            );

            position++;
            lastPos = position;
            
            if (firstOccurence){
                tokens.push_back(
                    str.substr(lastPos + 1, (str.size() - position) - 2)
                );
                break;
            }
        }
        return tokens;
    }
}

