#pragma once

#include <string>

#include <libfasthttpserver/common/headers/headers.h>
#include <libtcpserver/socket/socket.h>

struct Request {
    buffer_t body;
    std::string method;
    std::string path;
    Headers headers;
    std::string version;

    Request(buffer_t body, std::string method, std::string path, Headers headers, std::string version);
};