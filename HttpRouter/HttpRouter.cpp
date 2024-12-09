#include "../HttpR/HttpResponse.h"
#include "../HttpR/HttpRequest.h"
#include "../HttpRouter/HttpRouter.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <cstring>

std::string Router::getFileContent(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (file.is_open()) {
        std::ostringstream content;
        content << file.rdbuf();
        file.close();
        return content.str();
    }
    std::cerr << "[Router] Failed to open file: " << path << std::endl;
    return "";
}

std::string Router::getMimeType(const std::string& path) {
    static std::unordered_map<std::string, std::string> mimeTypes = {
        {".html", "text/html"},
        {".css", "text/css"},
        {".js", "application/javascript"},
        {".svg", "image/svg+xml"},
        {".jpg", "image/jpeg"},
        {".png", "image/png"},
        {".ico", "image/x-icon"}
    };
    auto extensionPos = path.find_last_of('.');
    if (extensionPos != std::string::npos) {
        auto extension = path.substr(extensionPos);
        if (mimeTypes.count(extension)) {
            return mimeTypes[extension];
        }
    }
    return "application/octet-stream";  // Default MIME type
}

httpResponse Router::serveStaticFile(const std::string& filePath) {
    httpResponse res;
    res.body = getFileContent(filePath);
    if (res.body.empty()) {
        return getNotFoundResponse();  // Return 404 if the file is not found
    }
    res.status_code = 200;
    res.headers.emplace_back("Content-Type", getMimeType(filePath));
    res.headers.emplace_back("Content-Length", std::to_string(res.body.size()));  // Add Content-Length header
    return res;
}

httpResponse Router::getNotFoundResponse() {
    httpResponse res;
    res.status_code = 404;
    res.status_message = "Not Found";
    res.body = "<h1>404 Not Found</h1>";
    res.headers.emplace_back("Content-Type", "text/html");
    return res;
}

httpResponse Router::handlePostRequest(httpRequest request) {
    httpResponse res;
    // Process POST data (e.g., handle form submissions, process JSON payload)
    res.status_code = 200;
    res.status_message = "OK";
    res.body = "<h1>POST request received</h1>";
    res.headers.emplace_back("Content-Type", "text/html");
    return res;
}

httpResponse Router::route(httpRequest request) {
    auto path = request.path;
    std::cout << "[Router] Request path: " << path 
              << ", method: " << request.method << std::endl;

    if (path == "/") {
        path = "/index.html";  // Default to the homepage
    }

    // Sanitizing the path to prevent directory traversal attacks
    if (path.find("..") != std::string::npos) {
        std::cerr << "[Router] Invalid path traversal attempt: " << path << std::endl;
        return getNotFoundResponse();
    }

    // Serve files from the `Website` directory
    std::string baseDir = "Website";
    std::string fullPath = baseDir + path;

    // Logging the full file path
    std::cout << "[Router] Serving file: " << fullPath << std::endl;

    // Handle different HTTP methods (GET, POST, etc.)
    if (request.method == "GET") {
        return serveStaticFile(fullPath);
    } else if (request.method == "POST") {
        return handlePostRequest(request);
    } else {
        std::cerr << "[Router] Unsupported method: " << request.method << std::endl;
        return getNotFoundResponse();
    }
}
