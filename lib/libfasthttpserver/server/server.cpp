#include "server.h"

// HTTPServer class constructor
HTTPServer::HTTPServer(int port): 
    server(port),
    port(port) {}

// HTTPServer class destructor
HTTPServer::~HTTPServer() {
    server.~socket_server();
}

// HTTPServer start method
void HTTPServer::start() {
    // Start the tcp server
    server.start();

    // Start the threads
    server_running = true;

    acceptor_thread = std::thread(acceptor, &server, &server_running);
    handler_thread = std::thread(handler, &server, &server_running);

}

// HTTPServer stop method
void HTTPServer::stop() {
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

void HTTPServer::handler(socket_server* server, std::atomic_bool* running) {
    while (*running) {

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}