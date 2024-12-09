#pragma once

#include "../Utils/Utils.h"
#include <string>

class Logger {
private:
    std::string _title;
    bool _logToFile;
    std::string _logFilePath;
    bool _logToConsole;
    bool _isClientConnected;  // Track if the server is currently logging for a client

public:
    Logger();
    Logger(std::string title);
    void log(std::string msg);
    void logToFile(std::string path);
    void logToConsole(std::string msg);  // Now accepts a string argument
    void clientConnected();  // Called when a client connects
    void clientDisconnected();  // Called when a client disconnects

private:
    std::string getTimestamp();  // Private method to get the timestamp
};
