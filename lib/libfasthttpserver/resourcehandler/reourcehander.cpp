#include "resourcehandler.h"
#include "resource/classes/request.h"
#include "resource/classes/response.h"

// Add resource handler to the server
void ResourceHandler::addResource(std::shared_ptr<Resource> resource) {
    // Get the path of the resource
    std::string path = resource->getPath();

    // Add the resource to the map
    resources[path] = resource;
}

// Handle the request
buffer_t ResourceHandler::handleRequest(Request& request) {
    // Get the path of the request
    std::string path = request.path;

    // Check if the resource exists
    if (resources.find(path) == resources.end()) {
        // Return a 404 response
        return Response::Get404Response().to_buffer();
    }

    // Get the resource
    std::shared_ptr<Resource> resource = resources[path];

    // Get the method of the request
    Method method = resource->getMethod();

    // Check if the method is correct
    if (method != method) {
        // Return a 405 response
        return Response::Get405Response().to_buffer();
    }

    // Render the resource
    Headers headers;

    // Set some pre headers
    headers.set("Date", Headers::get_date_formatted());

    Response response(headers);

    // Render the resource
    resource->render(request, response);

    // Return the response
    return response.to_buffer();
}