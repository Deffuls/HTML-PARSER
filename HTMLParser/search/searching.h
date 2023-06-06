#pragma once
#include "../types/types.h"
#include "../tags/html_tags.h"
#include "../signals/signals.h"
#include <string>
#include <iostream>
#include <map>

namespace Options{

    namespace MATCH_TYPES{
        enum STRING {
            STRICT_STR = 0,
            FIND_IN = 1,
        };
        
        enum ATTRIBUTES {
            FLEXIBLE = 2,
            STRICT_COUNT = 3
        };
    }


    struct SearchOption{
        public:
        SearchOption(std::string tagName, 
        MATCH_TYPES::STRING stringMatch=MATCH_TYPES::STRING::STRICT_STR,
        MATCH_TYPES::ATTRIBUTES attributesMatch=MATCH_TYPES::ATTRIBUTES::FLEXIBLE) : mTagName(tagName), mStringMatchType(stringMatch), mAttributesMatchType(attributesMatch) { mRequiredMatches = 1; }

        SearchOption(std::string tagName, mapAttributes attributes,
        MATCH_TYPES::ATTRIBUTES attributesMatch=MATCH_TYPES::ATTRIBUTES::FLEXIBLE,
        MATCH_TYPES::STRING stringMatch=MATCH_TYPES::STRING::STRICT_STR) : mTagName(tagName), mAttributes(attributes), mStringMatchType(stringMatch), mAttributesMatchType(attributesMatch) { mRequiredMatches = 2; }

        SearchOption(std::string tagName, mapAttributes attributes, bool matchAttributesCount, int searchDeep = 0,
        MATCH_TYPES::ATTRIBUTES attributesMatch=MATCH_TYPES::ATTRIBUTES::FLEXIBLE,
        MATCH_TYPES::STRING stringMatch=MATCH_TYPES::STRING::STRICT_STR)
        : mTagName(tagName), mSearchDeep(searchDeep), mAttributes(attributes), mStringMatchType(stringMatch), mAttributesMatchType(attributesMatch) {}

        private:
        mapAttributes mAttributes;
        std::string mTagName;
        int mSearchDeep;
        int mRequiredMatches;
        MATCH_TYPES::ATTRIBUTES mAttributesMatchType;
        MATCH_TYPES::STRING mStringMatchType;

        public:
        const mapAttributes& getAttributes(){
            return mAttributes;
        }

        std::string getTagName(){
            return mTagName;
        }

        MATCH_TYPES::STRING getStringMatchType(){
            return mStringMatchType;
        }

        MATCH_TYPES::ATTRIBUTES getAttributesMatchType(){
            return mAttributesMatchType;
        }

        int getRequiredMatches() {
            return mRequiredMatches;
        }
    };
}

namespace Search{

    namespace InternalUsage{

        void AttributesMatch(Options::MATCH_TYPES::ATTRIBUTES matchType, int foundCounter, int targetCount, int& outResult){

        switch (matchType)
        {
        case Options::MATCH_TYPES::ATTRIBUTES::STRICT_COUNT:
            if (foundCounter == targetCount){
                outResult++;
            }else {outResult = 0;}
            break;
        case Options::MATCH_TYPES::ATTRIBUTES::FLEXIBLE:
            if (foundCounter > 0 && foundCounter <= targetCount){
                outResult++;
            }
            else{ outResult = 0;}
            break;
        }

        }

        void StringMatch(auto target, auto match, Options::MATCH_TYPES::STRING matchType, int& matchCounter){

            switch (matchType)
            {
            case Options::MATCH_TYPES::STRING::STRICT_STR:
                if ( target == match){
                    matchCounter++;
                }
                break;
            
            case Options::MATCH_TYPES::STRING::FIND_IN:
                if (target.find(match) != std::string::npos){
                    matchCounter++;
                }
                break;
            }
        }
    }

    bool MatchElement(const WebElements::Html_Tag& Tag, Options::SearchOption& Option){
        
        int cMatch = 0;

        InternalUsage::StringMatch( Tag.getTagName(), Option.getTagName(), Option.getStringMatchType(), cMatch );

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
                    InternalUsage::StringMatch(tagBegin->second, optBegin->second, Option.getStringMatchType(), cOptMatches);
                }
             }

             // ( cOptMatches == cOptNeeded ) ? cMatch++ : cMatch = 0;
             InternalUsage::AttributesMatch(Option.getAttributesMatchType(), cOptMatches, cOptNeeded, cMatch);
        }
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
            return TAG_NOT_FOUND;
        }
    }
}