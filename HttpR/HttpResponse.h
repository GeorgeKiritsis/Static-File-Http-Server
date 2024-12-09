#ifndef __HTTP_RESPONSE_H__
#define __HTTP_RESPONSE_H__

#include "../Utils/Utils.h"

struct httpResponse {
    int status_code;                    // HTTP status code (e.g., 200, 404)
    std::string status_message;         // HTTP status message (e.g., OK, Not Found)
    std::vector<std::pair<std::string, std::string>> headers;  // Response headers
    std::string body;                   // Response body
};

#endif
