# HTTP Server Project in C++

## Overview

This project is a fully functional HTTP server written in **C++**. The server can handle basic HTTP methods like **GET** and **POST**, serve static files, and provide structured responses to clients. The implementation focuses on modular design and efficient handling of multiple client connections.

The primary components of the project are:

- **Logger**: Handles logging of server activity and errors.
- **Parser**: Parses incoming HTTP requests.
- **Router**: Routes requests to appropriate handlers and serves static files.
- **Server**: The core server that manages client connections and request handling.

## Features

### 1. **HTTP Request Parsing**
- The server parses incoming HTTP requests and extracts the request method, path, HTTP version, headers, and body.
- Cookies are automatically parsed from the `Cookie` header.

### 2. **Routing and Static File Serving**
- The server routes requests to appropriate handlers based on the HTTP method and URL path.
- It serves static files (e.g., HTML, CSS, JS, images) from a predefined directory (`Website`).
- MIME types are determined automatically based on file extensions.

### 3. **Logging**
- Comprehensive logging helps track server activity, errors, and client connections.
- Logs can be displayed in the console for real-time monitoring.

### 4. **Concurrent Connection Handling**
- The server can handle multiple clients concurrently using the `select()` system call.
- It maintains a list of active client connections and processes them efficiently.

### 5. **Error Handling**
- The server returns appropriate HTTP error responses, such as **404 Not Found** for missing resources.
- Proper error messages are logged for debugging purposes.

## Project Structure

The project consists of several key components, each encapsulated in a class:

- **`Logger`**:  
  Logs messages to the console or a log file.  
  - File: `HttpLogger/HttpLogger.h` and `HttpLogger/HttpLogger.cpp`

- **`HttpRequest` and `HttpResponse`**:  
  Represent HTTP request and response objects, respectively.  
  - Files: `HttpR/HttpRequest.h` and `HttpR/HttpResponse.h`

- **`Parser`**:  
  Decodes HTTP requests and encodes HTTP responses.  
  - Files: `HttpParser/HttpParser.h` and `HttpParser/HttpParser.cpp`

- **`Router`**:  
  Routes incoming requests to appropriate handlers and serves static files.  
  - Files: `HttpRouter/HttpRouter.h` and `HttpRouter/HttpRouter.cpp`

- **`HttpServer`**:  
  The core server that manages sockets, listens for connections, and handles client requests.  
  - Files: `HttpServer/HttpServer.h` and `HttpServer/HttpServer.cpp`

- **`Utils`**:  
  Utility functions such as string trimming and MIME type detection.  
  - Files: `Utils/Utils.h` and `Utils/Utils.cpp`

- **`main`**:  
  The entry point of the application where the server is initialized and run.  
  - File: `main.cpp`

## How It Works

1. **Initialization**:  
   - The server is initialized with a logger and a router.
   - The default address is set to `127.0.0.1` and the port to `8080`.

2. **Running the Server**:  
   - The server starts listening for incoming connections.
   - When a client connects, the server accepts the connection and reads the incoming request.

3. **Request Handling**:  
   - The request is parsed into an `HttpRequest` object.
   - The router processes the request and generates an appropriate `HttpResponse`.

4. **Serving Responses**:  
   - The response is encoded and sent back to the client.
   - The connection is then closed.

5. **Logging**:  
   - All significant actions, such as incoming requests, errors, and client disconnections, are logged for monitoring and debugging.

## Requirements

- **C++ Compiler** (GCC or Clang)
- **CMake** (for building the project)
- **POSIX-compliant system** (Linux/macOS)

## Build and Run Instructions

1. **Clone the Repository**:

   ```bash
   git clone <repository-url>
   cd <project-directory>
## Build the Project

    ```bash
    mkdir build
    cd build
    cmake ..
    make

2. Run the Server
    ```bash
    ./HttpServer

3. Access the Server

Open a web browser and navigate to:
    ```bash
    http://127.0.0.1:8080

Future Improvements

Support for additional HTTP methods like PUT and DELETE.
HTTPS support for secure communication.
Thread-based concurrency for improved performance with high loads.
Configuration file support for customizable server settings.

Conclusion

This project serves as a solid foundation for building more advanced HTTP servers. It provides an opportunity to explore networking, HTTP protocol handling, and modular software design in C++. The clean architecture allows for easy extension and maintenance, making it a versatile tool for learning and experimentation.
