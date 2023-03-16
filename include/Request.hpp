
#ifndef WEBSERV_H
# define WEBSERV_H
# include <string.h>
# include "Uri.hpp"
# include "MessageHeaders.hpp"

class Request
{
private:
public:
	Request(/* args */);
	~Request();
	std::string		method;
	std::string		protocol;
	std::string		body;
	Uri				target;
	MessageHeaders	headers;
	bool			parseResquest(const std::string &rawRequest, size_t & messageEnd);
	bool			parseResquest(const std::string &rawRequest);
};

#endif