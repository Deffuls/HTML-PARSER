#pragma once
#include "../signals/signals.h"
#include <string>

STATUS ReplaceString(std::string& subject, const std::string& search,
const std::string& replace) {
    std::size_t pos = 0;
    while ( (pos = subject.find(search, pos) ) != std::string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

STATUS ShrinkString(std::string& subject, const std::string& begin,
const std::string& end){
     std::size_t begin_pos = 0;
     std::size_t end_pos = 0;

     begin_pos = subject.find(begin, begin_pos);
     end_pos = subject.find(end, end_pos);

     if ( begin_pos == std::string::npos || end_pos == std::string::npos) { return STRING_NOT_FOUND; }

     std::size_t length = (end_pos - begin_pos) + end.size();
     subject = subject.substr(begin_pos, length);
     return SUCCESS;
}