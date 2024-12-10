#pragma once

#include "../HttpR/HttpRequest.h"
#include "../HttpR/HttpResponse.h"
#include "../HttpLogger/HttpLogger.h"
#include <string>

std::string encodeResponse(const httpResponse& response);

httpRequest decodeHttp(const std::string& msg, Logger& logger);
