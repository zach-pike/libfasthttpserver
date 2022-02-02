#pragma once

#include <vector>
#include <cstdint>

#include <libfasthttpserver/http/headers/headers.h>
#include <libfasthttpserver/http/responseline/responseline.h>
#include <libtcpserver/socket/socket.h>

namespace HTTP {
    class ResponseConstructor {
    public:
        static buffer_t construct_response(ResponseLine response_line, Headers headers, std::vector<uint8_t> body);
    };
}