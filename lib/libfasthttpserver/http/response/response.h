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

    // Set the http status code
    void setStatusCode(int status_code);

    // Get the http status message
    void setStatusMessage(std::string status_message);

    // Set the body of the response, WARNING: this will not set the Content-Length or Content-Type headers
    void setBody(buffer_t body);

    // Get the set status code
    int getStatusCode();

    // Get the set status message
    std::string getStatusMessage();

    // Get the set body of the response
    buffer_t getBody();

    // For basic responses, this will set the Content-Length header and the Content-Type header.
    void send(std::string str, std::string type);
    void send(buffer_t buffer, std::string type);

    // Convert the response to a string
    buffer_t to_buffer();
    
    // For generating static responses for 404, 405, etc.
    static Response GetStaticResponse(int code, std::string message, std::string body);
};