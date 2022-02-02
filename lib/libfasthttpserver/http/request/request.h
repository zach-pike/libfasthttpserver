#pragma once

#include <string>

#include "libfasthttpserver/http/headers/headers.h"
#include "libtcpserver/socket/socket.h"
#include "libfasthttpserver/http/methods/methods.h"

struct Request {
    buffer_t body;
    HTTP::Methods::Method method;
    std::string path;
    HTTP::Headers headers;
    std::string version;

    Request(buffer_t body, HTTP::Methods::Method method, std::string path, HTTP::Headers headers, std::string version);
};