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
buffer_t ResourceHandler::handleRequest(Request& request) {
    using namespace HTTP;

    // Get the path of the request
    std::string path = request.path;

    // Check if the resource exists
    if (resources.find(path) == resources.end()) {
        // Return a 404 response
        return Response::GetStaticResponse(404, "Not Found", "404: Resource not found").to_buffer();
    }

    // Get the resource
    std::shared_ptr<Resource> resource = resources[path];

    // Get the method of the request
    Methods::Method method = resource->getMethod();

    // Check if the method is correct
    if (method != request.method) {
        // Return a 405 response
        return Response::GetStaticResponse(405, "Method Not Allowed", "405: Method not allowed").to_buffer();
    }

    // Render the resource
    Headers headers;

    // Set some pre headers
    headers.set("Date", Headers::get_date_formatted());
    headers.set("Connection", "keep-alive");

    Response response(headers);

    // Render the resource
    resource->render(request, response);

    // Return the response
    return response.to_buffer();
}