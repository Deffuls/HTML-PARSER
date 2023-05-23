#pragma once
#include "../tags/html_tags.h"
#include "../formating/text.h"
#include "../types/types.h"
#include <string>
#include <stdexcept>

const std::map<std::string, int> cTagMap = {
        { "<base>", 1 },
        { "<style>", 2 },
        { "<script>", 3 },
        { "<body>", 4 },
        { "<article>", 5 },
        { "<section>", 6 },
        { "<nav>", 7 },
        { "<aside>", 8 },
        { "<h1>", 9 },
        { "<h2>", 10 },
        { "<h3>", 11 },
        { "<h4>", 12 },
        { "<h5>", 13 },
        { "<h6>", 14 },
        { "<header>", 15 },
        { "<footer>", 16 },
        { "<address>", 17 },
        { "<main>", 18 },
        { "<p>", 19 },
        { "<hr>", 20 },
        { "<pre>", 21 },
        { "<blockquote>", 22 },
        { "<ol>", 23 },
        { "<ul>", 24 },
        { "<li>", 25 },
        { "<dl>", 26 },
        { "<dt>", 27 },
        { "<dd>", 28 },
        { "<figure>", 29 },
        { "<figcaption>", 30 },
        { "<div>", 31 },
        { "<a>", 32 },
        { "<em>", 33 },
        { "<strong>", 34 },
        { "<small>", 35 },
        { "<s>", 36 },
        { "<cite>", 37 },
        { "<q>", 38 },
        { "<dfn>", 39 },
        { "<abbr>", 40 },
        { "<time>", 41 },
        { "<code>", 42 },
        { "<var>", 43 },
        { "<samp>", 44 },
        { "<kbd>", 45 },
        { "<sub>", 46 },
        { "<sup>", 47 },
        { "<i>", 48 },
        { "<b>", 49 },
        { "<mark>", 50 },
        { "<ruby>", 51 },
        { "<rt>", 52 },
        { "<rp>", 53 },
        { "<bdi>", 54 },
        { "<bdo>", 55 },
        { "<span>", 56 },
        { "<br>", 57 },
        { "<wbr>", 58 },
        { "<ins>", 59 },
        { "<del>", 60 },
        { "<img>", 61 },
        { "<iframe>", 62 },
        { "<embed>", 63 },
        { "<object>", 64 },
        { "<param>", 65 },
        { "<video>", 66 },
        { "<audio>", 67 },
        { "<source>", 68 },
        { "<track>", 69 },
        { "<map>", 70 },
        { "<area>", 71 },
        { "<table>", 72 },
        { "<caption>", 73 },
        { "<colgroup>", 74 },
        { "<col>", 75 },
        { "<tbody>", 76 },
        { "<thead>", 77 },
        { "<tfoot>", 78 },
        { "<tr>", 79 },
        { "<td>", 80 },
        { "<th>", 81 },
        { "<form>", 82 },
        { "<fieldset>", 83 },
        { "<legend>", 84 },
        { "<label>", 85 },
        { "<input>", 86 },
        { "<button>", 87 },
        { "<select>", 88 },
        { "<optgroup>", 89 },
        { "<option>", 90 },
        { "<textarea>", 91 },
        { "<output>", 92 },
        { "<progress>", 93 },
        { "<meter>", 94 },
        { "<details>", 95 },
        { "<summary>", 96 },
        { "<menu>", 97 },
        { "<menuitem>", 98 },
        { "<dialog>", 99 }
    };

mapAttributes ExtractAttributes(std::string& element){ // problem is related to this function somehow.
    mapAttributes attributes;

    std::size_t firstPos = element.find(" ", (std::size_t)0 );
    std::size_t lastPos = element.find(">", (std::size_t)0 );

    if (firstPos == std::string::npos) { return attributes; }
    
    firstPos++;

    std::string onlyAttributes = element.substr(firstPos, ( lastPos - firstPos ) );

    std::vector<std::string> vAttributes = Format::SplitString(onlyAttributes, ' ');

    for( std::string attr : vAttributes){

        std::vector<std::string> vKeyValue = Format::SplitString(attr, '=');
        
        std::string l1 = vKeyValue[0];
        std::string l2 = vKeyValue[1];

        attributes.emplace( vKeyValue[0], vKeyValue[1] );
    }
    element = element.substr(0, firstPos - 1) + ">";
    return attributes;
}


WebElements::Html_Tag CreateElement(std::string elementName){

    mapAttributes mAttributes = ExtractAttributes(elementName);
    std::map<std::string, int>::const_iterator tag = cTagMap.find(elementName);
    if( tag == cTagMap.end() ) { throw std::invalid_argument( (std::string("Unkown Element: ") + elementName) ); }
    WebElements::Html_Tag html_tag = { tag->second, tag->first, mAttributes};

    return html_tag;
}
