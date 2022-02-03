#include "server.h"
#include "parsers/requestparser/requestparser.h"
#include "http/responseline/responseline.h"
#include "http/responseconstructor/responseconstructor.h"
#include "http/headers/headers.h"

#include <iostream>
#include <optional>

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
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}

struct request_status {
    int body_bytes_needed;
    int body_bytes_received;

    bool header_complete;
    std::optional<Request> request;

    int body_start_index;
};

void HTTPServer::handler(socket_server* server, std::atomic_bool* running, ResourceHandler* resource_handler) {
    std::map<int, request_status> statuses;
    while (*running) {

        std::vector<int> sockets_to_close;

        // To be implemented 
        server->loop_over_clients([&](socket_client& socket) {
            // Check the buffer to see if we have a double CR+LF
            auto& buffer = socket.get_buffer();

            // Create a request status struct
            if (statuses.find(socket.get_client_fd()) == statuses.end()) {
                statuses[socket.get_client_fd()] = request_status{ 0, 0, false, {}, 0 };
            }

            // If there is no data in the buffer, return
            if (buffer.size() < 0) return;

            // Get the request status
            auto& status = statuses[socket.get_client_fd()];

            if (status.header_complete == false) {
                std::string buf_str = std::string(buffer.begin(), buffer.end());

                if (buf_str.find("\r\n\r\n") != std::string::npos) {
                    status.header_complete = true;
                    status.body_start_index = buf_str.find("\r\n\r\n") + 4;

                    // Parse the request, do not include the double CR+LF
                    auto parsed_request = Parsers::RequestParser::parse_request(buf_str.substr(0, status.body_start_index - 4));

                    // Get how many bytes we need to receive
                    if (parsed_request.headers.has("Content-Length")) {
                        status.body_bytes_needed = std::stoi(parsed_request.headers.get("Content-Length"));
                    } else {
                        status.body_bytes_needed = 0;
                    }

                    // Set the request
                    status.request = parsed_request;
                }
            } else {
                status.body_bytes_received = buffer.size() - status.body_start_index;

                if (status.body_bytes_needed == status.body_bytes_received) {
                    // We have received all the bytes, we can now construct the response

                    // Set the body in the request
                    status.request->body = buffer_t(buffer.begin() + status.body_start_index, buffer.end());

                    ResourceHandler::ResourceHandlerResult response_buffer = resource_handler->handleRequest(status.request.value());

                    // Send the response
                    socket.send_buffer((const char*)response_buffer.render.data(), response_buffer.render.size());

                    bool should_close_connection;

                    if (status.request->headers.has("Connection")) {
                        should_close_connection = status.request->headers.get("Connection") == "close";
                    } else {
                        should_close_connection = response_buffer.should_close_connection;
                    }

                    if (should_close_connection) {
                        sockets_to_close.push_back(socket.get_client_fd());
                    }


                    // Clear the buffer
                    buffer.clear();

                    // Reset the request status
                    status.header_complete = false;
                    status.body_bytes_needed = 0;
                    status.body_bytes_received = 0;
                    status.body_start_index = 0;
                    status.request = {};
                }
            }
        });

        for (auto& socket_fd : sockets_to_close) {
            server->close_client_by_fd(socket_fd);
            statuses.erase(statuses.find(socket_fd));
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}