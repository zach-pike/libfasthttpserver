#pragma once

#include <string>
#include <map>
#include <memory>

#include <libfasthttpserver/http/response/response.h>
#include <libfasthttpserver/http/request/request.h>
#include <libfasthttpserver/http/headers/headers.h>
#include <libfasthttpserver/resource/resource.h>

class ResourceHandler {
    public:
        void addResource(std::shared_ptr<Resource> resource);

        // Returns the rendered data for the request
        buffer_t handleRequest(Request& request);

    private:
        std::map<std::string, std::shared_ptr<Resource>> resources;
};