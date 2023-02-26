
#ifndef CONFIG_H
# define CONFIG_H
# include "../../include/webserv.hpp"
# include <string>

class Config
{
private:
	std::string severName;
	std::string location;
	std::string redirection;
	std::string ip;
	std::string defaultErrorPage;
	int			port;
	int			clientBodySize;
	bool		directoryList;

public:
	Config();
	~Config();
};

#endif
