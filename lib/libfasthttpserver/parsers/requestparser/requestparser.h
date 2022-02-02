#pragma once

#include <vector>
#include <string>

#include <libfasthttpserver/common/headers/headers.h>
#include <libfasthttpserver/resource/classes/request.h>

class RequestParser {
public:

    static Request parse_request(std::vector<uint8_t> request);
};