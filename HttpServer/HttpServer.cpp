#include "../HttpServer/HttpServer.h"
#include "../HttpLogger/HttpLogger.h"
#include "../HttpParser/httpParser.h"
#include "../HttpRouter/HttpRouter.h"
#include "../Utils/Utils.h"

HttpServer::HttpServer(Logger logger, Router router) {
    _logger = logger;
    _port = 8080;
    _address = "127.0.0.1";
    _maxClientsCount = 10;
    _router = router;
}

void HttpServer::setPort(int port) {
    _port = port;
}

void HttpServer::setAddress(std::string address) {
    _address = address;
}

void HttpServer::run() {
    initServerSocket();

    fd_set readfds;
    int maxFd = _serverSocket;
    std::vector<int> activeClients;

    while (true) {
        FD_ZERO(&readfds);
        FD_SET(_serverSocket, &readfds);  // Add the server socket to the set

        // Add all active client sockets to the set
        for (int clientSocket : activeClients) {
            FD_SET(clientSocket, &readfds);
            if (clientSocket > maxFd) {
                maxFd = clientSocket;
            }
        }

        // Wait for activity on any of the sockets
        int activity = select(maxFd + 1, &readfds, nullptr, nullptr, nullptr);
        if (activity < 0) {
            _logger.log("Error with select function: " + std::string(strerror(errno)));
            continue;
        }

        // Check if there's a new connection
        if (FD_ISSET(_serverSocket, &readfds)) {
            struct sockaddr_in clientAddr;
            socklen_t clientSize = sizeof(clientAddr);
            int clientSocket = accept(_serverSocket, (struct sockaddr*)&clientAddr, &clientSize);
            if (clientSocket < 0) {
                _logger.log("Error accepting client connection: " + std::string(strerror(errno)));
                continue;
            }

            // Log the first connection and add the client to the active list
            activeClients.push_back(clientSocket);
            _logger.log("New client connected: " + std::to_string(clientSocket));
        }

        // Handle all active client connections
        for (int clientSocket : activeClients) {
            if (FD_ISSET(clientSocket, &readfds)) {
                handleClient(clientSocket);

                // After handling the client, remove the socket from the active list
                activeClients.erase(std::remove(activeClients.begin(), activeClients.end(), clientSocket), activeClients.end());
                _logger.log("Client disconnected: " + std::to_string(clientSocket) + "\n");
            }
        }
    }

    close(_serverSocket);
}

void HttpServer::handleClient(int clientSocket) {
    const int BUFFER_SIZE = 4096;
    char buffer[BUFFER_SIZE];
    std::string requestMessage;

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (bytesReceived == -1) {
            _logger.log("Error receiving message from client: " + std::string(strerror(errno)));
            break;  // Break the loop instead of returning directly
        } else if (bytesReceived == 0) {
            _logger.log("Client disconnected.");
            break;  // Break the loop on client disconnect
        }

        requestMessage.append(buffer, bytesReceived);

        // Check if we have received the complete message
        if (requestMessage.find("\r\n\r\n") != std::string::npos) {
            break;  // Full message received
        }
    }

    if (!requestMessage.empty()) {
        auto request = decodeHttp(requestMessage, _logger);  // Decode the HTTP request
        _logger.log("Request received: " + request.method + " " + request.path);  // Log request details

        auto response = _router.route(request);  // Route the request
        _logger.log("Response status: " + std::to_string(response.status_code) + " " + response.status_message);

        std::string responseStr = encodeResponse(response);
        int bytesSent = send(clientSocket, responseStr.c_str(), responseStr.size(), 0);            
        if (bytesSent == -1) {
            _logger.log("Error sending response to client: " + std::string(strerror(errno)));
        }
    }

    close(clientSocket);  // Close the socket after completing communication
}

void HttpServer::initServerSocket() {
    // Create socket
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (_serverSocket == -1) {
        _logger.log("Error creating server socket: " + std::string(strerror(errno)));
        exit(EXIT_FAILURE);
    }

    // Config address
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET; // Use IPv4
    serverAddr.sin_port = htons(_port);
    if (inet_aton(_address.c_str(), &serverAddr.sin_addr) <= 0) {
        _logger.log("Error converting address: " + std::string(strerror(errno)));
        exit(EXIT_FAILURE);
    }

    // Bind socket
    if (bind(_serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        _logger.log("Error binding server socket: " + std::string(strerror(errno)));
        exit(EXIT_FAILURE);
    }

    // Set listener
    if (listen(_serverSocket, _maxClientsCount) == -1) {
        _logger.log("Error starting listener: " + std::string(strerror(errno)));
    } else {
        _logger.log("Server listening on " + _address + ":" + std::to_string(_port));
    }
}
