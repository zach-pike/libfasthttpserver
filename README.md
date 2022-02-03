## LibFastHTTPServer

A server for HTTP/1.1 to use for any general purpose http projects.

### Example
```c++
#include <libfasthttpserver/server/server.h>
#include <libfasthttpserver/resource/getresource.h>
#include <libfasthttpserver/resource/postresource.h>

#include <string>
#include <memory>

class HelloWorldResource : public GetResource {
    public:
        void render(const Request& request, Response& response) {
            response.send("Hello World!", "text/plain");
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

    // Pause the main thread
    int i;
    std::cin >> i;
    
    std::cout << "Stopping server" << std::endl;
    server.stop();


    return 0;
}

```
Makes a endpoint at http://localhost:8080/hello that will return "Hello World!"

---

## Installation
Just two commands:
```bash
make build
sudo make install
```
