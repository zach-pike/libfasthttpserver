#pragma once

#include <libtcpserver/server/server.h>
#include <thread>
#include <atomic>

class HTTPServer {
    private:
        int port;

        socket_server server;

        std::atomic_bool server_running;

        std::thread acceptor_thread;
        static void acceptor(socket_server* server, std::atomic_bool* running);
        
        std::thread handler_thread;
        static void handler(socket_server*, std::atomic_bool* running);

    public:
        HTTPServer(int port);
        ~HTTPServer();

        void start();
        void stop();
};