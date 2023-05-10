#pragma once
#include "../types/types.h"
#include "../tags/html_tags.h"
#include "../signals/signals.h"
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

        public:
        const mapAttributes& getAttributes(){
            return mAttributes;
        }

        std::string getTagName(){
            return mTagName;
        }

        void setTagName(std::string tagName){
            mTagName = tagName;
        }

        void setAttributes(mapAttributes attributes){
            mAttributes = attributes;
        }

        void extendAttributes(mapAttributes newAttributes){
            mAttributes.insert(newAttributes.begin(), newAttributes.end());
        }

        void appendAttribute(std::string attribute, std::string value){
            mAttributes.emplace(attribute, value);
        }

    };
}

namespace Search{

    bool MatchElement(const WebElements::Html_Tag& Tag, Options::SearchOption& Option){
        if ( Tag.getTagName().find( Option.getTagName() ) != std::string::npos ){
            return true;
        }
        return false;
    }

    namespace TREE{
        
        STATUS FindElement(const WebElements::Html_Tag& Tag, WebElements::Html_Tag& OutTag, Options::SearchOption& Option){
            for(const WebElements::Html_Tag& childTag : Tag.mChildsVector){
                if ( MatchElement(childTag, Option) ){
                    OutTag = childTag;
                    return TAG_FOUND;
                }
                if ( FindElement(childTag, OutTag, Option) == TAG_FOUND ){
                    return TAG_FOUND;
                }
            }
            return TAG_NOT_FOUND;
        }
        
        STATUS FindRootByChild(const WebElements::Html_Tag& Tag, const Options::SearchOption& Option){        

        }

    }
}