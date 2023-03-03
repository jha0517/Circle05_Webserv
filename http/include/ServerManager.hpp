#ifndef SERVERMANAGER_H
# define SERVERMANAGER_H
# include "Request.hpp"
# include "Response.hpp"
# include <stdexcept>
# include <stack>
# include <iostream>
# include <fstream>
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <string.h>
# include "stdlib.h"

class Config;
class Request;
class Response;

class ServerManager
{
private:
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
