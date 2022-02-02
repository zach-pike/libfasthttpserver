#include <libfasthttpserver/server/server.h>
#include <libfasthttpserver/resource/getresource.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class HelloWorldResource : public GetResource {
    public:
        void render(const Request& request, Response& response) {
            response.setStatusCode(200);
            response.headers.set("Content-Type", "text/html; charset=utf-8");

            std::stringstream ss;
            ss << std::ifstream("test.html").rdbuf();
            response.setBody(buffer_t{ ss.str().begin(), ss.str().end() });
            response.headers.set("Content-Length", std::to_string(ss.str().size()));
        }

        std::string getPath() const {
            return "/hello";
        }
};

int main() {
    HTTPServer server(8080);

    auto resource = std::make_shared<HelloWorldResource>();

    server.resourceHandler.addResource(resource);

    server.start();

    int i;
    std::cin >> i;
    
    std::cout << "Stopping server" << std::endl;
    server.stop();


    return 0;
}