#ifndef SERVERMANAGER_H
# define SERVERMANAGER_H
# include "../../include/webserv.hpp"
# include "../src/server/Config.hpp"
# include "../src/server/Request.hpp"
# include "../src/server/Response.hpp"

class Config;
class Request;
class Response;

class ServerManager
{
private:
    struct sockaddr_in	address;
	int					serverFd;
	Request				request;
	Response			response;

public:
	ServerManager();
	~ServerManager();
	void		printLog();
	void		setConfiguration(char *configFile, char **env);
	void		runServer(unsigned int port);

	class errorMsg : public std::exception
	{
		private:
			const char *message;
		public:
			explicit errorMsg(const char *message);
			virtual const char *what() const throw();
	};
};

#endif