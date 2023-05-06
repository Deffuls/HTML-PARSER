#pragma once
#include <vector>
#include <string>
#include <map>

namespace TagMap{
    
    const std::map<std::int16_t, std::string> cTagMap = {
        { 0, "<p>" },
        { 1, "<h1>" },
        { 2, "<h2>" },
        { 3, "<h3>" },
        { 4, "<h4>" },
        { 5, "<h5>" },
        { 6, "<h6>" },
        { 7, "<strong>" },
        { 8, "<address>" },
        { 9, "<div>" },
        { 10, "<a>" },
        { 11, "<ul>" },
        { 12, "<li>" },
        { 13, "<tr>" },
        { 14, "<td>" },
        { 15, "<tbody>" },
        { 16, "<body>"},
        { 17, "<button>"}
    };
}

namespace WebElements{

    struct Html_Tag{
        public:
        explicit Html_Tag(std::int16_t tagCode, std::string tagName) : mTagCode(tagCode), mTagName(tagName) {};

        private:
        std::vector<Html_Tag> mChildsVector;
        std::map<std::string, std::string> mAttributes;
        std::int16_t mTagCode;
        std::string mTagName;

        public:
        std::string getTag() const {
            return mTagName;
        }

        std::string getAttribute() const {
            return std::string();
        }

        void AppendChild(Html_Tag child){
            mChildsVector.push_back(child);
        }
        
    };
}