#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace WebElements{
    
    struct Html_Tag{
        public:
        Html_Tag(int tagCode, std::string tagName, std::size_t tagEndPos) : mTagCode(tagCode), mTagName(tagName), mTagEndPos(tagEndPos) {};
        Html_Tag() = default;
        std::vector<Html_Tag> mChildsVector;
        private:
        std::map<std::string, std::string> mAttributes;
        std::string mTagName;
        int mTagCode;
        std::size_t mTagEndPos;

        public:

        void setTagCode(int tagCode) {
            mTagCode = tagCode;
        }

        void setTagName(std::string tagName) {
            mTagName = tagName;
        }

        std::size_t getTagEndPos() const{
            return mTagEndPos;
        }
        
        std::string getTagName() const {
            return mTagName;
        }

        std::string getAttribute() const {
            return std::string();
        }

        void AppendChild(Html_Tag child){
            mChildsVector.push_back(child);
        }

        bool isClosingTag(std::string& element){
            return element.find("/", 0) == std::string::npos ? false : true;
        }

    };
}