
#ifndef WEBSERV_H
# define WEBSERV_H
# include <string.h>
# include "Uri.hpp"
# include "MessageHeaders.hpp"

struct	Request{
	std::string		method;
	std::string		body;
	Uri				target;
	MessageHeaders	headers;
};

#endif