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
    struct sockaddr_in	address;
	int					serverFd;
	Request				*request;
	Response			*response;

public:
	ServerManager();
	~ServerManager();
	void		printLog();
	void		setConfiguration(char *configFile, char **env);
	void		runServer(char *ip);
	Request		*getValidRequest(char *buffer);
	Response	*createResponse(Request *request);
};

#endif