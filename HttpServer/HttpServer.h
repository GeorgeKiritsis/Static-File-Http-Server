#pragma once

#include "../HttpLogger/HttpLogger.h"
#include "../HttpRouter/HttpRouter.h"

class HttpServer {
    private:
        Logger _logger;
        int _port;
        std::string _address;
        int _serverSocket;
        int _maxClientsCount;
        void initServerSocket();
        void handleClient(int clientSocket);
        Router _router;
    public:
        HttpServer(Logger logger, Router router);
        void setPort(int port);
        void setAddress(std::string address);
        void run();
};
