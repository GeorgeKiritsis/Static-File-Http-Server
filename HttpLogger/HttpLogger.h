#pragma once

#include "../Utils/Utils.h"
#include <string>

class Logger {
private:
    std::string _title;
    bool _logToFile;
    std::string _logFilePath;
    bool _logToConsole;
    bool _isClientConnected;  

public:
    Logger();
    Logger(std::string title);
    void log(std::string msg);
    void logToFile(std::string path);
    void logToConsole(std::string msg);  
    void clientConnected();  
    void clientDisconnected();  

private:
    std::string getTimestamp(); 
};
