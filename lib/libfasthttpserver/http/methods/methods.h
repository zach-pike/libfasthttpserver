#pragma once

#include <string>

namespace HTTP::Methods {
    enum class Method {
        GET,
        POST,
        PUT,
        DELETE,
        HEAD,
        OPTIONS,
        TRACE,
        CONNECT,
        PATCH,
        UNKNOWN
    };

    // Convert a string to a Method enum
    Method getMethod(const std::string& method);

    // Convert a Method enum to a string
    std::string getMethodString(Method method);
}