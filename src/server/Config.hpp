
#ifndef CONFIG_H
# define CONFIG_H
# include "../../include/webserv.hpp"
# include <string>

class Config
{
private:
	std::string serverName;
	std::string location;
	std::string redirection;
	std::string defaultErrorPage;
	unsigned int	port;
	int			clientBodySize;
	bool		directoryList;

public:
	Config();
	~Config();
	void	parsing(char *configFile, char **env);
	void	init();
	std::string	getServerName();
	unsigned int	getPort();
};

#endif
