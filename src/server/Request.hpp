#ifndef REQUEST_H
# define REQUEST_H

enum Method { GET, POST, DELETE};

class Request
{
private:
	unsigned int _method;
public:
	Request();
	~Request();
	void			parsing(char *raw);
	unsigned int	getMethod() const;
};

#endif