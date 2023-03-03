#include "../include/Request.hpp"

Request::Request(/* args */)
{
}

Request::~Request()
{
}

void Request::parsing(char *raw)
{
	(void) raw;
}

unsigned int Request::getMethod() const{
	return (_method);
}
