#pragma once

#include <string>
#include <libfasthttpserver/http/headers/headers.h>
#include <libtcpserver/socket/socket.h>

class Response {
private:
    int status_code = 200;
    std::string status_message = "OK";
    buffer_t body;
public:    
    HTTP::Headers headers;

    Response(HTTP::Headers headers);

    void setStatusCode(int status_code);
    void setStatusMessage(std::string status_message);
    void setBody(buffer_t body);

    int getStatusCode();
    std::string getStatusMessage();
    buffer_t getBody();

    buffer_t to_buffer();

    static Response GetStaticResponse(int code, std::string message, std::string body);
};