#include "resourcehandler.h"
#include "http/request/request.h"
#include "http/response/response.h"
#include "http/methods/methods.h"

// Add resource handler to the server
void ResourceHandler::addResource(std::shared_ptr<Resource> resource) {
    // Get the path of the resource
    std::string path = resource->getPath();

    // Add the resource to the map
    resources[path] = resource;
}

// Handle the request
ResourceHandler::ResourceHandlerResult ResourceHandler::handleRequest(Request& request) {
    using namespace HTTP;

    bool should_close_connection = false;

    // Get the path of the request
    std::string path = request.path;

    // Check if the resource exists
    if (resources.find(path) == resources.end()) {
        // Return a 404 response
        return ResourceHandlerResult{ Response::GetStaticResponse(404, "Not Found", "404: Resource not found").to_buffer(), true };
    }

    // Get the resource
    std::shared_ptr<Resource> resource = resources[path];

    // Get the method of the request
    Methods::Method method = resource->getMethod();

    // Check if the method is correct
    if (method != request.method) {
        // Return a 405 response
        return ResourceHandlerResult{ Response::GetStaticResponse(405, "Method Not Allowed", "405: Method not allowed").to_buffer(), true };
    }

    // Render the resource
    Headers headers;

    Response response(headers);

    // Render the resource
    resource->render(request, response);

    if (response.getStatusCode() > 299) {
        should_close_connection = true;
    }

    // Set some pre headers
    response.headers.set("Date", Headers::get_date_formatted());
    if (should_close_connection) {
        response.headers.set("Connection", "close");
    } else {
        response.headers.set("Connection", "keep-alive");
    }

    // Return the response
    return ResourceHandlerResult{ response.to_buffer(), should_close_connection };
}