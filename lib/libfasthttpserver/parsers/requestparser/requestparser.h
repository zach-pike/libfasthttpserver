#pragma once

#include <vector>
#include <string>

#include <libfasthttpserver/common/headers/headers.h>

class RequestParser {
public:
    struct Request {
        std::string method;
        std::string path;
        std::string version;
        Headers headers;
    };

    static Request parse_request(std::vector<uint8_t> request);
};