
#include "../include/Response.hpp"

Response::Response()
{
	// start.insert(std::pair<std::string, std::string>("204", "No Content"));
	// header.insert(std::pair<std::string, std::string>("Content-Type", "text/html"));
}

Response::~Response()
{

}

void	Response::send(int fd){

	//text/plain
	// std::string test = "HTTP/1.1 200 OK\r\nContent-Length: 22\r\nContent-Type: text/plain\r\n\r\nThis is Hyunah, World!";
	// write(fd, test.c_str(), test.length());

	// text/html
	std::string test = "HTTP/1.1 200 OK\r\nContent-Length: 22\r\nContent-Type: text/plain\r\n\r\nThis is Hyunah, World!";
	write(fd, test.c_str(), test.length());












	// write(fd, "HTTP/1.1 ", 9);
	// for (std::map<std::string, std::string>::const_iterator it = start.begin(); it != start.end(); it++)
	// {
	// 	std::string ss;

	// 	ss = it->first + " " + it->second;
	// 	// std::cout << ss;
	// 	// write(fd, ss.c_str(), ss.length());
	// }
	// write(fd, "\r\n", 2);

	// for (std::map<std::string, std::string>::const_iterator it = header.begin(); it != header.end(); it++)
	// {
	// 	std::string ss;

	// 	ss = it->first + " : " + it->second + "\r\n";
	// 	write(fd, ss.c_str(), ss.length());
	// }
	// std::string hello = "Hello from server\n";
	// write(fd, hello.c_str(), hello.length());
}
