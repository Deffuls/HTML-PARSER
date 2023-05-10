#pragma once
#include "../types/types.h"
#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace WebElements{
    
    struct Html_Tag{
        public:
        Html_Tag(int tagCode, 
        std::string tagName, 
        mapAttributes tagAttributes) : mTagCode(tagCode), mTagName(tagName), mTagAttributes(tagAttributes) {};
        
        Html_Tag() = default;
        std::vector<Html_Tag> mChildsVector;
        private:
        mapAttributes mTagAttributes;
        std::string mTagText;
        std::string mTagName;
        int mTagCode;

        public:

        Html_Tag& getLastCreatedChild(){
            return mChildsVector.back();
        }

        void addTagText(std::string tagText){
            mTagText.append(tagText);
        }

        std::string getTagText() {
            return mTagText;
        }

        void setTagCode(int tagCode) {
            mTagCode = tagCode;
        }

        void setTagName(std::string tagName) {
            mTagName = tagName;
        }

        const mapAttributes& getTagAttributes() {
            return mTagAttributes;
        }
        
        std::string getTagName() const {
            return mTagName;
        }

        void AppendChild(Html_Tag child){
            mChildsVector.push_back(child);
        }

        bool isClosingTag(std::string& element){
            std::string closingTag = mTagName.substr(1, mTagName.size() - 2);

            return element.find("/", 0) != std::string::npos &&
            element.find(closingTag) != std::string::npos ? true : false;
        }

    };
}