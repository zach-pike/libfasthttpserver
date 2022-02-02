#include "request.h"

// Request constructor
Request::Request(buffer_t body, std::string method, std::string path, Headers headers, std::string version) {
    this->body = body;
    this->method = method;
    this->path = path;
    this->headers = headers;
    this->version = version;
}