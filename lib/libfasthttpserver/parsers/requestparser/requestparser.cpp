#include "requestparser.h"
#include "http/request/request.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>

std::vector<std::string> split_string_by_delim(std::string haystack, std::string needle) {
    std::vector<std::string> tokens;

    size_t start = 0;
    size_t end = haystack.find(needle);
    while (end != std::string::npos) {
        tokens.push_back(haystack.substr(start, end - start));

        start = end + needle.length();

        end = haystack.find(needle, start);
    }

    tokens.push_back(haystack.substr(start, end));

    return tokens;
}


// RequestParser parse request method
Request Parsers::RequestParser::parse_request(std::string request) {
    // Parse request line
    std::stringstream reqline;

    size_t reqlineEnd = request.find("\r\n");

    // holy fuck
    reqline << request.substr(0, reqlineEnd);
    
    std::string method;
    std::string path;
    std::string version;

    // Parse the request line
    reqline >> method >> path >> version;

    // Parse the headers
    // We will split the headers into lines
    std::string headers_str = request.substr(reqlineEnd + 2);

    HTTP::Headers reqheaders;

    for (auto token : split_string_by_delim(headers_str, "\r\n")) {
        std::string name;
        std::string value;
        
        // Get the name
        name = token.substr(0, token.find(":"));

        // Now we need to find where the header starts by finding the first
        // nonspace value after the :
        size_t header_value_start = token.find(":") + 1;

        for (; header_value_start < token.size(); header_value_start++) {
            if (token[header_value_start] != ' ') break;
        }

        value = token.substr(header_value_start);

        reqheaders.set(name, value);
    }

    buffer_t body;

    Request req(body, HTTP::Methods::getMethod(method), path, reqheaders, version);

    return req;
}