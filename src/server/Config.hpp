
#ifndef CONFIG_H
# define CONFIG_H
# include "../../include/webserv.hpp"

class Config
{
private:
	std::string severName;
	std::string location;
	std::string ip;
public:
	Config();
	~Config();
};

#endif
