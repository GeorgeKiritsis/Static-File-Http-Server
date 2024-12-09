#pragma once

#include "../HttpR/HttpRequest.h"
#include "../HttpR/HttpResponse.h"

class Router {
private:
    // Utility functions to handle file content and MIME types
    std::string getFileContent(const std::string& path);
    std::string getHtmlContent(const std::string& path);
    std::string getMimeType(const std::string& path);
    
    // Serve static files like HTML, CSS, JS, images, etc.
    httpResponse serveStaticFile(const std::string& filePath);
    
    // Helpers to generate error responses
    httpResponse getNotFoundResponse();
    httpResponse getBadRequestResponse(const std::string& msg);
    
    // Helpers to generate HTML pages for common routes
    httpResponse getHtmlPageResponse(const std::string& pageName);
    
    // Route-specific handlers for different pages or endpoints
    httpResponse homePage(httpRequest request);
    httpResponse aboutPage(httpRequest request);
    httpResponse updatesPage(httpRequest request);
    
    // Handle POST request logic (you can extend this later)
    httpResponse handlePostRequest(httpRequest request);

public:
    // Main routing function that processes the incoming request
    httpResponse route(httpRequest request);
    
    // Optionally, add helpers for handling other HTTP methods, like PUT, DELETE, etc.
    httpResponse handlePutRequest(httpRequest request);
    httpResponse handleDeleteRequest(httpRequest request);
};
