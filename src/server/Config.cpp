
#include "../../include/webserv.hpp"

Config::Config() : serverName("127.0.0.1"), location("/"), redirection("/"), defaultErrorPage(""),  port(8080)
{
}

Config::~Config()
{
}

void	Config::parsing(char *configFile, char **env){
	(void) env;
	(void) configFile;
}

std::string	Config::getServerName(){
	return (serverName);
}

unsigned int	Config::getPort(){
	return (port);
}
