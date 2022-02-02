#include "server.h"
#include "parsers/requestparser/requestparser.h"
#include "common/responseline/responseline.h"
#include "common/responseconstructor/responseconstructor.h"
#include "common/headers/headers.h"

#include <iostream>

// HTTPServer class constructor
HTTPServer::HTTPServer(int port): 
    server(port),
    port(port),
    server_running(false) {}

// HTTPServer class destructor
HTTPServer::~HTTPServer() {
    stop();
}

// HTTPServer start method
void HTTPServer::start() {
    if (server_running == true) return;

    // Start the tcp server
    server.start();

    // Start the threads
    server_running = true;

    acceptor_thread = std::thread(acceptor, &server, &server_running);
    handler_thread = std::thread(handler, &server, &server_running, &resourceHandler);

}

// HTTPServer stop method
void HTTPServer::stop() {
    if (server_running == false) return;

    // Close the threads
    server_running = false;

    acceptor_thread.join();
    handler_thread.join();

    // Stop the tcp server
    server.stop();
}

void HTTPServer::acceptor(socket_server* server, std::atomic_bool* running) {
    while (*running) {
        server->accept_connections();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void HTTPServer::handler(socket_server* server, std::atomic_bool* running, ResourceHandler* resource_handler) {
    while (*running) {

        // To be implemented 
        server->loop_over_clients([&](socket_client& socket) {
            // Check the buffer to see if we have a double CR+LF
            auto& buffer = socket.get_buffer();
            std::string buf_str = std::string{ buffer.begin(), buffer.end() };

            if (buf_str.find("\r\n\r\n") != std::string::npos) {
                auto header = std::string{ (char*)buf_str.data(), buf_str.find("\r\n\r\n") };
                auto parsed = RequestParser::parse_request(buffer_t{ header.begin(), header.end() });

                // Pass the request to the resource handler
                auto response = resource_handler->handleRequest(parsed);

                // Send the response buffer
                socket.send_buffer((const char*)response.data(), response.size());

                buffer = buffer_t{};
            }
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}