#pragma once
#include "../tags/html_tags.h"
#include "../formating/text.h"
#include "../types/types.h"
#include "map_tags.h"
#include <string>
#include <stdexcept>


mapAttributes ExtractAttributes(std::string& element){
    mapAttributes attributes;                         

    std::size_t startPos = element.find(" ");
    if (startPos == std::string::npos) { return attributes; }
    startPos = startPos + (std::size_t)1;
    std::vector<std::string> allAttributes;
    
    std::string attr;
    int bracketsOpen = 0;
    for ( int index=(int)startPos; index <= element.size(); index++){
        char ch = element[index];

        switch (ch)
        {
        case '"':
            attr += ch;
            bracketsOpen++;
            if (bracketsOpen == 2){
                allAttributes.push_back(std::string(attr));
                attr.clear();
                bracketsOpen = 0;
            }
            break;
        
        case '>':
            allAttributes.push_back(std::string(attr));
            attr.clear();
            break;
        
        case ' ':
            if (bracketsOpen == 0){
                allAttributes.push_back(std::string(attr));
                attr.clear();
            }
            attr += ch;
            break;
        
        default:
            attr += ch;
            break;
        }
    }

    for (std::string attr : allAttributes){

        if (attr.find("=") != std::string::npos){
            std::vector<std::string> splittedAttributes = Format::SplitString(attr, '=', true);
            attributes.emplace(splittedAttributes[0], splittedAttributes[1]);
        }else if(attr.size() > 3){
            attributes.emplace(attr, "");
        }
    }
    element = element.substr(0, startPos - (std::size_t)1) + ">";

    return attributes;
}


WebElements::Html_Tag CreateElement(std::string elementName){

    mapAttributes mAttributes = ExtractAttributes(elementName);
    std::map<std::string, int>::const_iterator tag = cTagMap.find(elementName);
    if( tag == cTagMap.end() ) { throw std::invalid_argument( (std::string("Unkown Element: ") + elementName) ); }
    WebElements::Html_Tag html_tag = { tag->second, tag->first, mAttributes};

    return html_tag;
}
