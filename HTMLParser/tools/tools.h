#pragma once
#include "../tags/html_tags.h"
#include "../builder/tag_builder.h"
#include <string>

struct FunctionResponse{
     public:
     std::size_t lastPosition;
     FunctionResponse() = default;
     FunctionResponse(std::size_t pos){
          lastPosition = pos;
     }
};

std::string ExtractTag(std::string& htmlContent, std::size_t& startPos, std::size_t& stopPos, std::size_t& cpyLastPos, std::size_t& lastPos){
     cpyLastPos = lastPos;
     stopPos++;
     lastPos = stopPos;
     std::size_t length = (stopPos - startPos);
     return htmlContent.substr(startPos, length);
}

void AppendText(std::string& htmlContent, WebElements::Html_Tag& self, std::size_t startPos, std::size_t stopPos, std::size_t cpyLastPos){
     if ( startPos - stopPos > 0 ) {
          std::string tagText;
               std::size_t localLength = startPos - cpyLastPos;
               tagText = htmlContent.substr(cpyLastPos, localLength);
               self.addTagText(tagText);
          }
}

FunctionResponse ParseElements(std::string& htmlContent, WebElements::Html_Tag& itself, std::size_t lastPos){
     
     for (;;){
          std::size_t start_pos = htmlContent.find('<', lastPos );
          std::size_t stop_pos = htmlContent.find('>', lastPos );
          
          if ( start_pos == std::string::npos || stop_pos == std::string::npos) { return FunctionResponse(std::string::npos ); }
          
          {
               std::size_t cpyLastPos;
               std::string element = ExtractTag(htmlContent, start_pos, stop_pos, cpyLastPos, lastPos);
               AppendText(htmlContent, itself, start_pos, stop_pos, cpyLastPos);
               
               if ( itself.isClosingTag(element) ) { return FunctionResponse(lastPos); }
               
               WebElements::Html_Tag child = CreateElement(element);
               itself.AppendChild(child);

               if ( itself.isTagWithNoClose(element) ) { continue; }
          }

          FunctionResponse fResponse = ParseElements(htmlContent, itself.getLastCreatedChild(), lastPos);
          
          lastPos = fResponse.lastPosition;
          
          if (fResponse.lastPosition == std::string::npos) { return fResponse; }
     }
}