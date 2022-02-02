#include "request.h"
#include "http/methods/methods.h"

// Request constructor
Request::Request(buffer_t body, HTTP::Methods::Method method, std::string path, HTTP::Headers headers, std::string version) {
    this->body = body;
    this->method = method;
    this->path = path;
    this->headers = headers;
    this->version = version;
}