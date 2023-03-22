
#ifndef REQUEST_H
# define REQUEST_H
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
	// std::string		body;
	std::vector<char>	body;
	Uri				target;
	MessageHeaders	headers;
	bool			parseResquest(const std::vector<char> rawRequest, size_t & messageEnd);
	bool			parseResquest(const std::vector<char> rawRequest);
	// bool			parseResquest(const std::string &rawRequest, size_t & messageEnd);
	// bool			parseResquest(const std::string &rawRequest);
};

#endif