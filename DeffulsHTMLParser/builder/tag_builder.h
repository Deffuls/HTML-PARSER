#pragma once
#include "../tags/html_tags.h"
#include <string>
#include <stdexcept>

const std::map<std::string, int> cTagMap = {
        { "<p>", 0 },
        { "<h1>", 1 },
        { "<h2>", 2 },
        { "<h3>", 3 },
        { "<h4>", 4 },
        { "<h5>", 5 },
        { "<h6>", 6 },
        { "<strong>", 7 },
        { "<address>", 8 },
        { "<div>", 9 },
        { "<a>", 10 },
        { "<ul>", 11 },
        { "<li>", 12 },
        { "<tr>", 13 },
        { "<td>", 14 },
        { "<tbody>", 15 },
        { "<body>", 16 },
        { "<button>", 17 }
    };

WebElements::Html_Tag CreateElement(std::string elementName, std::size_t stop_pos){
    std::map<std::string, int>::const_iterator tag = cTagMap.find(elementName);
    if( tag == cTagMap.end() ) { throw std::invalid_argument( (std::string("Unkown Element: ") + elementName) ); }
    WebElements::Html_Tag html_tag = { tag->second, tag->first , stop_pos};
    return html_tag;
}
