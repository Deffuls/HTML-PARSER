#include "DeffulsHTMLParser/HTMLParser.h"
#include "DeffulsHTMLParser/tags/html_tags.h"
#include "DeffulsHTMLParser/search/searching.h"
#include "DeffulsHTMLParser/signals/signals.h"
#include <string>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream myfile;
    myfile.open("test.html");
    std::string fileContents((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
    myfile.close();

    HtmlParser parser = { fileContents };
    WebElements::Html_Tag root;
    parser.ParseHTML(root);

    Options::SearchOption myOption;
    myOption.setTagName("<h2>");
    WebElements::Html_Tag resultTag;
    
    STATUS result = Search::TREE::FindElement(root, resultTag, myOption);

    if (result == TAG_FOUND){
        std::cout << "Found Tag -> " << resultTag.getTagName() << std::endl;
    }
    else{
        std::cout << "Not Found" << std::endl;
    }
    return 0;
}