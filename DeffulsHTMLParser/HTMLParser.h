#pragma once
#include "signals/signals.h"
#include "tags/html_tags.h"
#include "tools/tools.h"

#include <string>
#include <iostream>

class HtmlParser{

    private:
    STATUS mReady;
    bool mReceiveErrors;
    std::string mHtmlContent;

    public:
    HtmlParser(std::string htmlPage="", bool receiveErrors=false){
        mHtmlContent = htmlPage;
        mReceiveErrors = receiveErrors;
        mReady = (htmlPage.size() == 0) ? NOT_READY : READY;
    }

    void LoadHTML(std::string htmlPage, bool receiveErrors=false){
        mHtmlContent = htmlPage;
        mReceiveErrors = receiveErrors;
        mReady = (htmlPage.size() == 0) ? NOT_READY : READY;
    }

    STATUS ParseHTML(WebElements::Html_Tag& rootElement){
        if (mReady != READY) { return HTML_NOT_FOUND; }
        std::size_t stop_pos = mHtmlContent.find('>');

        {
            Format::ReplaceString(mHtmlContent, "\n", "");
            Format::ShrinkString(mHtmlContent, "<body>", "</body>");

            std::size_t start_pos = mHtmlContent.find('<');
            
            if ( start_pos == std::string::npos || stop_pos == std::string::npos) { throw std::invalid_argument( "Unable to Locate Any < > Symbol." ); }
            stop_pos++;

            std::size_t length = (stop_pos - start_pos);
            std::string element = mHtmlContent.substr(start_pos, length);

            rootElement = CreateElement(element);
        }

        ParseElements(mHtmlContent, rootElement, stop_pos);

        return SUCCESS;
    }
};