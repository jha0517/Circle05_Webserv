## Webserv

This repository contains my solution to the Webserv project at 42. The project involves creating a web server that can handle HTTP requests and responses, including parsing and validating headers, handling GET and POST requests, and serving static and dynamic content.

### How to use

1. Clone the repository
2. Navigate to the root directory of the project
3. Run `make` to build the executable
4. Run the executable with `./webserv <config_file>`

### Configuration

Webserv is configured using a JSON file. The file specifies the server's port number, the document root, and the mapping of file extensions to CGI programs. An example configuration file is included in this repository.

### Features

- Handles HTTP/1.1 requests
- Supports GET and POST requests
- Serves static and dynamic content
- Supports CGI programs for dynamic content
- Parses and validates request headers
- Provides error responses for common HTTP errors

### Resources

- [RFC 2616 - Hypertext Transfer Protocol -- HTTP/1.1](https://tools.ietf.org/html/rfc2616)
- [Nginx Documentation](https://nginx.org/en/docs/)
- [CGI Tutorial](https://www.tutorialspoint.com/cgi/index.htm)
