#pragma once

#include <libfasthttpserver/resource/resource.h>
#include <libfasthttpserver/HTTP/methods/methods.h>

class GetResource : public Resource {
    public:
        // Forward the function call to the render method of the derived class
        virtual void render(const Request& request, Response& response) = 0;

        // Returns the path of the resource
        virtual std::string getPath() const = 0;
        
        virtual HTTP::Methods::Method getMethod() const {
            return HTTP::Methods::Method::GET;
        }
};