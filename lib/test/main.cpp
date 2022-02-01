#include <libfasthttpserver/server/server.h>

#include <string>
#include <iostream>

int main() {
    // Test http request string
    HTTPServer server(8080);

    server.start();

    std::this_thread::sleep_for(std::chrono::seconds(10));
    
    std::cout << "Stopping server" << std::endl;
    server.stop();


    return 0;
}