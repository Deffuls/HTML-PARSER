#pragma once
#include "signals/signals.h"
#include "tags/html_tags.h"
#include "tools/tools.h"

#include <string>
#include <algorithm>
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
    ~HtmlParser(){

    }

    void LoadHTML(std::string htmlPage, bool receiveErrors=false){
        mHtmlContent = htmlPage;
        mReceiveErrors = receiveErrors;
        mReady = (htmlPage.size() == 0) ? NOT_READY : READY;
    }

    STATUS ParseHTML(){
        if (mReady != READY) { return HTML_NOT_FOUND; }
        ReplaceString(mHtmlContent, "\n", "");
        ShrinkString(mHtmlContent, "<body>", "</body>");


        
        std::cout << mHtmlContent << std::endl;
        return SUCCESS;
    }
};