#pragma once

#include <string>

#include <libfasthttpserver/common/headers/headers.h>
#include <libtcpserver/socket/socket.h>

class Request {
    private:
        buffer_t body;
        std::string method;
    public:
        Headers headers;

        

};