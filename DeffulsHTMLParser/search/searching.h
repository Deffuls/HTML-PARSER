#pragma once
#include "../types/types.h"
#include "../tags/html_tags.h"
#include "../signals/signals.h"
#include <string>
#include <iostream>
#include <map>

namespace Options{

    enum MATCH_TYPES {
        STRICT = 0,
        FIND_IN = 1
    };

    struct SearchOption{
        public:
        SearchOption(std::string tagName, MATCH_TYPES matchType=STRICT) : mTagName(tagName), mMatchType(matchType) { mRequiredMatches = 1; }
        SearchOption(std::string tagName, mapAttributes attributes, MATCH_TYPES matchType=STRICT) : mTagName(tagName), mAttributes(attributes), mMatchType(matchType) { mRequiredMatches = 2; }
        SearchOption(std::string tagName, mapAttributes attributes, bool matchAttributesCount, int searchDeep = 0, MATCH_TYPES matchType=STRICT)
        : mTagName(tagName), mSearchDeep(searchDeep), mAttributes(attributes), mMatchType(matchType) {}

        private:
        mapAttributes mAttributes;
        std::string mTagName;
        int mSearchDeep;
        int mRequiredMatches;
        MATCH_TYPES mMatchType;

        public:
        const mapAttributes& getAttributes(){
            return mAttributes;
        }

        std::string getTagName(){
            return mTagName;
        }

        MATCH_TYPES getMatchType(){
            return mMatchType;
        }

        int getRequiredMatches() {
            return mRequiredMatches;
        }
    };
}

namespace Search{

    namespace InternalUsage{

        void StringMatch(auto target, auto match, Options::MATCH_TYPES matchType, int& matchCounter){

            switch (matchType)
            {
            case Options::MATCH_TYPES::STRICT:
                if ( target == match){
                    matchCounter++;
                }
                break;
            
            case Options::MATCH_TYPES::FIND_IN:
                if (target.find(match) != std::string::npos){
                    matchCounter++;
                }
                break;
            }
        }
        
    }

    bool MatchElement(const WebElements::Html_Tag& Tag, Options::SearchOption& Option){
        
        int cMatch = 0;

        InternalUsage::StringMatch( Tag.getTagName(), Option.getTagName(), Option.getMatchType(), cMatch );

        const mapAttributes TagAttr = Tag.getTagAttributes();
        const mapAttributes OptAttr = Option.getAttributes();

        if ( TagAttr.size() > 0 && OptAttr.size() > 0 ){

            int cOptMatches = 0;
            std::size_t cOptNeeded = OptAttr.size();

            mapAttributes::const_iterator optBegin = OptAttr.begin();
            mapAttributes::const_iterator tagBegin = TagAttr.begin();

             for(optBegin; optBegin != OptAttr.end(); optBegin++){

                if ( TagAttr.find(optBegin->first) == TagAttr.end() ) { continue; }

                for ( tagBegin; tagBegin != TagAttr.end(); tagBegin++ ){
                    InternalUsage::StringMatch(tagBegin->second, optBegin->second, Option.getMatchType(), cOptMatches);
                }
             }

             ( cOptMatches == cOptNeeded ) ? cMatch++ : cMatch = 0 ;
        }
        std::cout << "MATCH " << cMatch << " / " << Option.getRequiredMatches() << std::endl;
        return (cMatch == Option.getRequiredMatches() ) ? true : false;
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