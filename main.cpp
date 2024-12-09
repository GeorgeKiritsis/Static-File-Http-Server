#include "./HttpLogger/HttpLogger.h"
#include "./HttpServer/HttpServer.h"
#include <exception>


int main(int argc, char **argv)
{
    Logger logger = Logger("Server");
    logger.logToConsole("Logger initialized");  // Log message for initialization

    try {
        Router router = Router();

        HttpServer server = HttpServer(logger, router);
        logger.logToConsole("Server is starting...");  // Log the starting message
        server.run();
    } catch (const std::exception& e) {
        logger.logToConsole("Error: " + std::string(e.what()));  // Log error message
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
