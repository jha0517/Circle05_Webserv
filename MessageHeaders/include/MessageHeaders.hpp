
#ifndef MessageHeaders_H
# define MessageHeaders_H
# include <string>
# include <vector>
# include <iostream>
# include <sstream>

class MessageHeaders
{
public:

	struct	Header{
		std::string	name;
		std::string	value;
	};
	typedef		std::vector<Header> Headers;

	bool		parseFromString(const std::string &rawMsg);
	Headers 	getHeaders() const;
	std::string	getHeaderValue(std::string name) const;
	bool		hasHeader(const std::string &name) const;
	std::string	getBody() const;
	void		setBody(const std::string newBody);
	std::string	generateRawMsg();

	MessageHeaders();
	~MessageHeaders();

private:
	Headers		headers;
	std::string	body;
};

#endif
