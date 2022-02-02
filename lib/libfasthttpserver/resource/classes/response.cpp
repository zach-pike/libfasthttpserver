#include "response.h"

#include "http/responseconstructor/responseconstructor.h"
#include "http/responseline/responseline.h"

#include <string>

// Response constructor
Response::Response(HTTP::Headers headers) {
    this->headers = headers;
}

// Response::setStatusCode
void Response::setStatusCode(int status_code) {
    this->status_code = status_code;
}

// Response::setStatusMessage
void Response::setStatusMessage(std::string status_message) {
    this->status_message = status_message;
}

// Response::setBody
void Response::setBody(buffer_t body) {
    this->body = body;
}

// Response::getStatusCode
int Response::getStatusCode() {
    return this->status_code;
}

// Response::getStatusMessage
std::string Response::getStatusMessage() {
    return this->status_message;
}

// Response::getBody
buffer_t Response::getBody() {
    return this->body;
}



// Response::Get405Response
Response Response::GetStaticResponse(int code, std::string message, std::string body) {
    HTTP::Headers headers;
    headers.set("Content-Type", "text/html");
    Response response(headers);
    response.setStatusCode(code);
    response.setStatusMessage(message);

    response.setBody(buffer_t(body.begin(), body.end()));
    response.headers.set("Content-Length", std::to_string(body.size()));
    return response;
}

// Response::to_string
buffer_t Response::to_buffer() {
    HTTP::ResponseLine response_line("HTTP/1.1", std::to_string(this->status_code), this->status_message);
    return HTTP::ResponseConstructor::construct_response(response_line, this->headers, this->body);
}