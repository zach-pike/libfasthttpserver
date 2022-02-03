#pragma once

#include <string>
#include <libfasthttpserver/http/request/request.h>
#include <libfasthttpserver/http/response/response.h>
#include <libfasthttpserver/http/methods/methods.h>


class Resource {
    public:
        // Returns the rendered data for the request
        virtual void render(const Request& request, Response& response) = 0;

        // Get the path this request is effective for
        virtual std::string getPath() const = 0;

        // Get the method this request is effective for
        virtual HTTP::Methods::Method getMethod() const = 0;
};