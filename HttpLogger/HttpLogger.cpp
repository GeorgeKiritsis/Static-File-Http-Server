#include "../HttpLogger/HttpLogger.h"

Logger::Logger() : _title("Log"), _logToConsole(false), _logToFile(false), _logFilePath(""), _isClientConnected(false) {}

Logger::Logger(std::string title) : _title(title), _logToConsole(false), _logToFile(false), _logFilePath(""), _isClientConnected(false) {}

void Logger::log(std::string msg) {
    std::string formattedMessage = "[" + _title + "] " + getTimestamp() + " " + msg;

    // Log to console
    if (_logToConsole) {
        std::cout << formattedMessage << std::endl;
    }

    // Log to file
    if (_logToFile) {
        std::ofstream outFile(_logFilePath, std::ios::app); // Append mode
        if (outFile.is_open()) {
            outFile << formattedMessage << std::endl;
            outFile.close();
        } else {
            std::cerr << "[Logger] Error: Cannot write to file: " << _logFilePath << std::endl;
        }
    }
}

void Logger::logToFile(std::string path) {
    std::ofstream outFile(path, std::ios::app);  // Check if file is writable
    if (outFile.is_open()) {
        _logFilePath = path;
        _logToFile = true;
        outFile.close();
    } else {
        std::cerr << "[Logger] Error: Cannot open file: " << path << std::endl;
    }
}

void Logger::logToConsole(std::string msg) {
    std::string formattedMessage = "[" + _title + "] " + getTimestamp() + " " + msg;
    _logToConsole = true;
    std::cout << formattedMessage << std::endl;  // Print the message to the console
}

void Logger::clientConnected() {
    if (!_isClientConnected) {
        // If no client is currently connected, insert a blank line to separate blocks
        log("");  // Insert a blank line for separation
    }
    _isClientConnected = true;
}

void Logger::clientDisconnected() {
    if (_isClientConnected) {
        log("");  // Insert a blank line after the client disconnects
    }
    _isClientConnected = false;
}

std::string Logger::getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[100];
    if (std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now))) {
        return buf;
    }
    return "unknown-time";
}
