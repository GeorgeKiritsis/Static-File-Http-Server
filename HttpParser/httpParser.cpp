#include "../HttpR/HttpResponse.h"
#include "../HttpR/HttpRequest.h"
#include "../HttpLogger/HttpLogger.h"
#include "../HttpParser/httpParser.h"

// Helper to trim whitespace
std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

httpRequest decodeHttp(const std::string& msg, Logger& logger) {
    httpRequest request;
    std::istringstream iss(msg);
    std::string line;

    // Parse request line
    if (std::getline(iss, line)) {
        std::istringstream firstLine(line);
        if (!(firstLine >> request.method >> request.path >> request.version)) {
            logger.log("Error: Invalid request line format");
            return request; // Return empty request if format is invalid
        }
    } else {
        logger.log("Error: Empty request line");
        return request; // Return empty request if no request line is found
    }

    // Parse headers
    while (std::getline(iss, line) && !line.empty()) {
        line = trim(line);
        size_t pos = line.find(':');
        if (pos != std::string::npos) {
            std::string key = trim(line.substr(0, pos));
            std::string value = trim(line.substr(pos + 1));
            request.headers[key] = value;

            // Parse cookies
            if (key == "Cookie") {
                std::istringstream cookiesStream(value);
                std::string cookie;
                while (std::getline(cookiesStream, cookie, ';')) {
                    size_t eqPos = cookie.find('=');
                    if (eqPos != std::string::npos) {
                        std::string cookieKey = trim(cookie.substr(0, eqPos));
                        std::string cookieValue = trim(cookie.substr(eqPos + 1));
                        request.cookies[cookieKey] = cookieValue;
                    }
                }
            }
        }
    }

    // Parse body
    std::string body((std::istreambuf_iterator<char>(iss)), std::istreambuf_iterator<char>());
    request.body = body;

    return request;
}

std::string encodeResponse(const httpResponse& response) {
    std::ostringstream oss;

    // Status line
    oss << "HTTP/1.1 " << response.status_code << " " << response.status_message << "\r\n";

    // Headers
    bool hasContentLength = false;
    for (const auto& header : response.headers) {
        oss << header.first << ": " << header.second << "\r\n";
        if (header.first == "Content-Length") {
            hasContentLength = true;
        }
    }

    // Add Content-Length if not already present
    if (!response.body.empty() && !hasContentLength) {
        oss << "Content-Length: " << response.body.size() << "\r\n";
    }

    // End headers
    oss << "\r\n";

    // Body
    if (!response.body.empty()) {
        oss << response.body;
    }

    return oss.str();
}
