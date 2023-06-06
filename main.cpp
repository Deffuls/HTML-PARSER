#include "HTMLParser/HTMLParser.h"
#include "HTMLParser/tags/html_tags.h"
#include "HTMLParser/search/searching.h"
#include "HTMLParser/signals/signals.h"
#include "HTMLParser/types/types.h"
#include <string>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream myfile;
    myfile.open("test2.html");
    std::string fileContents((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
    myfile.close();

    HtmlParser parser = { fileContents };
    WebElements::Html_Tag root;
    parser.ParseHTML(root);

    Options::SearchOption myOption( std::string("<input>"), {{"type", "text"}, {"name", "query"}, {"class", "form-control"}});
    WebElements::Html_Tag resultTag;
    
    STATUS result = Search::TREE::FindElement(root, resultTag, myOption);

    if (result == TAG_FOUND){
        std::cout << "Found Tag -> " << resultTag.getTagName() << std::endl;
        auto tags = resultTag.getTagAttributes();
        for( auto it=tags.begin(); it != tags.end(); it++){
            std::cout << it->first << "  " << it->second << std::endl;
        }
    }
    else{
        std::cout << "Not Found" << std::endl;
    }
    return 0;
}