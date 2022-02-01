#pragma once

#include <vector>
#include <cstdint>

#include <libfasthttpserver/common/headers/headers.h>
#include <libfasthttpserver/common/responseline/responseline.h>

class ResponseConstructor {
public:
    static std::vector<uint8_t> construct_response(ResponseLine response_line, Headers headers, std::vector<uint8_t> body);
};