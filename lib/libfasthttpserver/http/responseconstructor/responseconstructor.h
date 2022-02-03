#pragma once

#include <vector>
#include <cstdint>

#include <libfasthttpserver/http/headers/headers.h>
#include <libfasthttpserver/http/responseline/responseline.h>
#include <libtcpserver/socket/socket.h>

namespace HTTP::ResponseConstructor {
    // Take a response line and headers and a body and construct a response
    buffer_t construct_response(ResponseLine response_line, Headers headers, buffer_t body);
}