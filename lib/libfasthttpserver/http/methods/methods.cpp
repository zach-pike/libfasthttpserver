#include "http/methods/methods.h"

// HTTP::Methods::getMethod
HTTP::Methods::Method HTTP::Methods::getMethod(const std::string& method) {
    if (method == "GET") {
        return Method::GET;
    } else if (method == "POST") {
        return Method::POST;
    } else if (method == "PUT") {
        return Method::PUT;
    } else if (method == "DELETE") {
        return Method::DELETE;
    } else if (method == "HEAD") {
        return Method::HEAD;
    } else if (method == "OPTIONS") {
        return Method::OPTIONS;
    } else if (method == "TRACE") {
        return Method::TRACE;
    } else if (method == "CONNECT") {
        return Method::CONNECT;
    } else if (method == "PATCH") {
        return Method::PATCH;
    } else {
        return Method::UNKNOWN;
    }
}

// HTTP::Methods::getMethodString
std::string HTTP::Methods::getMethodString(Method method) {
    if (method == Method::GET) {
        return "GET";
    } else if (method == Method::POST) {
        return "POST";
    } else if (method == Method::PUT) {
        return "PUT";
    } else if (method == Method::DELETE) {
        return "DELETE";
    } else if (method == Method::HEAD) {
        return "HEAD";
    } else if (method == Method::OPTIONS) {
        return "OPTIONS";
    } else if (method == Method::TRACE) {
        return "TRACE";
    } else if (method == Method::CONNECT) {
        return "CONNECT";
    } else if (method == Method::PATCH) {
        return "PATCH";
    } else {
        return "UNKNOWN";
    }
}