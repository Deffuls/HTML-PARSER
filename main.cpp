#include "DeffulsHTMLParser/HTMLParser.h"
#include <string>
#include <fstream>
#include <iostream>

int main(){
    std::ifstream myfile;
    myfile.open("test.html");
    std::string fileContents((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
    myfile.close();

    HtmlParser parser = { fileContents };
    parser.ParseHTML();
    return 0;
}