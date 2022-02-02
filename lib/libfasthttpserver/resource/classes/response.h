#pragma once

#include <string>
#include <libfasthttpserver/common/headers/headers.h>
#include <libtcpserver/socket/socket.h>

class Response {
private:
    int status_code = 200;
    std::string status_message = "OK";
    buffer_t body;
public:    
    Headers headers;

    Response(Headers headers);

    void setStatusCode(int status_code);
    void setStatusMessage(std::string status_message);
    void setBody(buffer_t body);

    int getStatusCode();
    std::string getStatusMessage();
    buffer_t getBody();

    buffer_t to_buffer();

    static Response Get404Response();
    static Response Get405Response();
};