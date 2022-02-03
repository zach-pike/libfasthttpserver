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
        struct ResourceHandlerResult {
            buffer_t render;
            bool should_close_connection;
        };

        // Add a resource to the handler
        void addResource(std::shared_ptr<Resource> resource);

        // Returns the rendered data for the request
        ResourceHandlerResult handleRequest(Request& request);

    private:
        std::map<std::string, std::shared_ptr<Resource>> resources;
};