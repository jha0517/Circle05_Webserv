
#ifndef REQUEST_H
# define REQUEST_H
# include <string.h>
# include "Uri.hpp"
# include "MessageHeaders.hpp"
# include "utils.hpp"

class Request
{
private:
public:
	Request();
	~Request();
	Request(Request const &src);
	Request &operator=(Request const &rhs);

	std::string			method;
	std::string			protocol;
	std::vector<char>	body;
	Uri					target;
	MessageHeaders		headers;
	bool				parseResquest(const std::vector<char> rawRequest, size_t & messageEnd);
	bool				parseResquest(const std::vector<char> rawRequest);
};

#endif