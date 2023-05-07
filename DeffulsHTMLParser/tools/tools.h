#pragma once
#include "../signals/signals.h"
#include "../tags/html_tags.h"
#include "../builder/tag_builder.h"
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

std::size_t ParseElements(std::string& htmlContent, WebElements::Html_Tag& root, std::size_t lastPos){ // body
     WebElements::Html_Tag child;

     do
     {
          {
          
          std::size_t start_pos = htmlContent.find('<', lastPos );
          std::size_t stop_pos = htmlContent.find('>', lastPos );
          
          if ( start_pos == std::string::npos || stop_pos == std::string::npos) { throw std::invalid_argument( "Unable to Locate Any < > Symbol." ); }
          stop_pos++;
          lastPos = stop_pos;
          
          std::size_t length = (stop_pos - start_pos);
          std::string element = htmlContent.substr(start_pos, length);

          if ( root.isClosingTag(element) ) { std::cout << "CLOSING TAG " << element << std::endl; return lastPos; }
          
          child = CreateElement(element, stop_pos);
          root.AppendChild(child);

          }

          lastPos = ParseElements(htmlContent, child, lastPos);

     }while(true);
}