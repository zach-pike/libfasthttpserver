#include "responseconstructor.h"

// ResponseConstructor construct_response method
buffer_t HTTP::ResponseConstructor::construct_response(ResponseLine response_line, Headers headers, std::vector<uint8_t> body) {
    buffer_t result;

    auto response_line_string = response_line.to_string();
    auto headers_string = headers.to_string();

    if (body.size() > 0) {
        headers.set("Content-Length", std::to_string(body.size()));
    }

    result.insert(result.end(), response_line_string.begin(), response_line_string.end());
    result.insert(result.end(), headers_string.begin(), headers_string.end());

    if (body.size() > 0) {
        result.insert(result.end(), body.begin(), body.end());
    }

    return result;
}