#pragma once
#include "../types/types.h"
#include "../builder/map_tags.h"
#include "../formating/text.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace WebElements{
    
    struct Html_Tag{
        public:
        Html_Tag() = default;
        Html_Tag(int tagCode, 
        std::string tagName, 
        mapAttributes tagAttributes) : mTagCode(tagCode), mTagName(tagName), mTagAttributes(tagAttributes) {
        };
        std::vector<Html_Tag> mChildsVector;

        private:
        mapAttributes mTagAttributes;
        std::string mTagText;
        std::string mTagName;
        int mTagCode;

        public:
        const std::string& getTagText() const {
            return mTagText;
        }

        const mapAttributes& getTagAttributes() const {
            return mTagAttributes;
        }
        
        std::string getTagName() const {
            return mTagName;
        }

        Html_Tag& getLastCreatedChild(){
            return mChildsVector.back();
        }

        void addTagText(std::string tagText){
            mTagText.append(tagText);
        }

        void AppendChild(Html_Tag child){
            mChildsVector.push_back(child);
        }

        bool isTagWithNoClose(std::string& element){
            std::string onlyTag = Format::CopyUntil(element, {' ', '>'}) + ">";

            return cTagCloseMap.find(onlyTag) != cTagCloseMap.end();
        }

        bool isClosingTag(std::string& element){

            std::string tagNameClear =  "</" + mTagName.substr(1, mTagName.size() - 2);

            return element.find("/", 0) != std::string::npos &&
            element.find( tagNameClear ) != std::string::npos ? true : false;
        }

    };
}