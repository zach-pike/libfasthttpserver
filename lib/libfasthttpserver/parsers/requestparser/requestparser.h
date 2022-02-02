#pragma once

#include <vector>
#include <string>

#include <libfasthttpserver/http/headers/headers.h>
#include <libfasthttpserver/resource/classes/request.h>

namespace Parsers {
    class RequestParser {
    public:

        static Request parse_request(buffer_t request);
    };
}