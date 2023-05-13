#pragma once
#include "../types/types.h"
#include "../tags/html_tags.h"
#include "../signals/signals.h"
#include <string>
#include <map>

namespace Options{

    struct SearchOption{
        public:
        SearchOption(std::string tagName) : mTagName(tagName) {}
        SearchOption(std::string tagName, mapAttributes attributes, bool matchAttributesCount, int searchDeep = 0)
        : mTagName(tagName), mSearchDeep(searchDeep), mAttributes(attributes) {}
        
        private:
        mapAttributes mAttributes;
        std::string mTagName;
        int mSearchDeep;
        int mRequiredMatches;

        public:
        const mapAttributes& getAttributes(){
            return mAttributes;
        }

        std::string getTagName(){
            return mTagName;
        }
    };
}

namespace Search{

    bool MatchElement(const WebElements::Html_Tag& Tag, Options::SearchOption& Option){
        int cMatch = 0;
        
        if ( Tag.getTagName().find( Option.getTagName() ) != std::string::npos ){
            cMatch++;
        }

        const mapAttributes TagAttr = Tag.getTagAttributes();
        const mapAttributes OptAttr = Option.getAttributes();

        if ( TagAttr.size() > 0 && OptAttr.size() > 0 ){

            std::size_t cOptMatches = 0;
            std::size_t cOptNeeded = OptAttr.size();

            mapAttributes::const_iterator tagBegin = TagAttr.begin();
            mapAttributes::const_iterator optBegin = OptAttr.begin();

             for(optBegin; optBegin != OptAttr.end(); optBegin++){ // "key" : "value", "key1": "value1"
                if (optBegin->first.size() > 0 ){

                }

                if(optBegin->second.size() > 0){

                }

             }
             ( cOptMatches == cOptNeeded ) ? cMatch++ : 0 ;
        }

        return (cMatch > 0) ? true : false;
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