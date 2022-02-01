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
    handler_thread = std::thread(handler, &server, &server_running);

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

void HTTPServer::handler(socket_server* server, std::atomic_bool* running) {
    while (*running) {

        // To be implemented 
        server->loop_over_clients([&](socket_client& socket) {
            // Check the buffer to see if we have a double CR+LF
            auto& buffer = socket.get_buffer();
            std::string buf_str = std::string{ buffer.begin(), buffer.end() };

            if (buf_str.find("\r\n\r\n") != std::string::npos) {
                auto header = std::string{ (char*)buf_str.data(), buf_str.find("\r\n\r\n") };

                auto parsed = RequestParser::parse_request(buffer_t{ header.begin(), header.end() });

                std::cout << parsed.method << "\n";

                Headers respheaders;
                respheaders.set("Content-Type", "text/plain; charset=UTF-8");
                respheaders.set("Connection", "close");
                respheaders.set("Date", Headers::get_date_formatted());
                respheaders.set("Content-Length", "12");

                std::string msg = "Hello World!";

                ResponseLine respline("HTTP/1.1", "200", "OK");

                buffer_t response = ResponseConstructor::construct_response(respline, respheaders, buffer_t{ msg.begin(), msg.end() });

                std::cout << std::string{ response.begin(), response.end() } << "\n";

                if (parsed.method == "GET") {
                    socket.send_buffer((const char*)response.data(), response.size());
                }

                buffer = buffer_t{};
            }
        });

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}