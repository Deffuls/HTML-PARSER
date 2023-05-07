#include "DeffulsHTMLParser/HTMLParser.h"
#include "DeffulsHTMLParser/tags/html_tags.h"
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

    return 0;
}