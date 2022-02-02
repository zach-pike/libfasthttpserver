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

    Method getMethod(const std::string& method);
    std::string getMethodString(Method method);
}