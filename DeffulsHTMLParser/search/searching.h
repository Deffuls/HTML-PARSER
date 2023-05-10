#pragma once
#include "../types/types.h"
#include "../tags/html_tags.h"
#include <string>

namespace Options{

    struct SearchOption{
        public:
        SearchOption() = default;
        SearchOption(std::string tagName, mapAttributes attributes, int searchDeep = 0) : mTagName(tagName), mSearchDeep(searchDeep), mAttributes(attributes) {}
        private:
        mapAttributes mAttributes;
        std::string mTagName;
        int mSearchDeep;
    };
}

namespace Search{
    
    const WebElements::Html_Tag& FindElement(const WebElements::Html_Tag& Tag, Options::SearchOption Option){

    }

    const WebElements::Html_Tag& FindRootByChild(const WebElements::Html_Tag& Tag, Options::SearchOption Option){
        
    }
}