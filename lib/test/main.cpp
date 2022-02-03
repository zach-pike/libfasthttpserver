#include <libfasthttpserver/server/server.h>
#include <libfasthttpserver/resource/getresource.h>
#include <libfasthttpserver/resource/postresource.h>

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class HelloWorldResource : public GetResource {
    public:
        void render(const Request& request, Response& response) {
            response.setStatusCode(200);
            response.headers.set("Content-Type", "text/html; charset=utf-8");

            std::cout << "Connecton: " << request.headers.get("Connection") << std::endl;

            std::stringstream ss;
            ss << std::ifstream("test.html").rdbuf();
            response.setBody(buffer_t{ ss.str().begin(), ss.str().end() });
            response.headers.set("Content-Length", std::to_string(ss.str().size()));
        }

        std::string getPath() const {
            return "/hello";
        }
};

class MyPostResource : public PostResource {
    private:
        int counter = 0;

    public:
        void render(const Request& request, Response& response) {
            std::string body = std::string(request.body.begin(), request.body.end());
            body.append(std::to_string(counter));
            response.send(request.body, "text/plain");
        }

        std::string getPath() const {
            return "/post";
        }
};


int main() {
    HTTPServer server(8080);

    auto resource = std::make_shared<HelloWorldResource>();
    auto post_resource = std::make_shared<MyPostResource>();

    server.resourceHandler.addResource(resource);
    server.resourceHandler.addResource(post_resource);

    server.start();

    getchar();
    
    std::cout << "Stopping server" << std::endl;
    server.stop();


    return 0;
}