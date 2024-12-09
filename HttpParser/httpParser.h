#pragma once

#include "../HttpR/HttpRequest.h"
#include "../HttpR/HttpResponse.h"
#include "../HttpLogger/HttpLogger.h"
#include <string>

// Function to encode an httpResponse object into a string suitable for sending as an HTTP response
std::string encodeResponse(const httpResponse& response);

// Function to decode an HTTP request string into an httpRequest object
httpRequest decodeHttp(const std::string& msg, Logger& logger);
