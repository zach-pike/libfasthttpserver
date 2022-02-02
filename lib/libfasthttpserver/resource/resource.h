#pragma once

#include <string>
#include <libfasthttpserver/http/request/request.h>
#include <libfasthttpserver/http/response/response.h>
#include <libfasthttpserver/http/methods/methods.h>


class Resource {
    public:

        virtual void render(const Request& request, Response& response) = 0;

        virtual std::string getPath() const = 0;
        virtual HTTP::Methods::Method getMethod() const = 0;
};