#ifndef SERVERMANAGER_H
# define SERVERMANAGER_H
# include "../../include/webserv.hpp"

class Config;
class Request;
class Response;

class ServerManager
{
private:
	std::vector<Config> config;
	int	serverFd;
    struct sockaddr_in address;
	Request *request;
	Response *response;

public:
	ServerManager();
	~ServerManager();
	void		printLog();
	void		setConfiguration(char *configFile, char **env);
	void		createServer();
	void		runServer();
	Request		*getValidRequest(char *buffer);
	Response	*createResponse(Request *request);
};

#endif