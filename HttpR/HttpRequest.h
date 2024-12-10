#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "../Utils/Utils.h"

struct httpRequest {
    std::string method;                            // HTTP method (e.g., GET, POST)
    std::string path;                             // Request path
    std::string version;                          // HTTP version (e.g., HTTP/1.)1)
    std::map<std::string, std::string> headers;   // Request headers (using std::map)
    std::string body;                             // Request body
    std::map<std::string, std::string> cookies;   // Cookies
};

#endif
