#pragma once

#include <string>
#include <libfasthttpserver/resource/classes/request.h>
#include <libfasthttpserver/resource/classes/response.h>
#include <libfasthttpserver/http/methods/methods.h>


class Resource {
    public:

        virtual void render(const Request& request, Response& response) = 0;

        virtual std::string getPath() const = 0;
        virtual HTTP::Methods::Method getMethod() const = 0;
};