
#include "../include/Uri.hpp"
#include <iostream>

Uri::Uri() : scheme (""), host(""), splitchar("/"), port(0), existPort(true), existPath(false)
{
}

Uri::~Uri()
{
}

bool	Uri::ParsingFromString(const std::string & uriString){
	scheme = "";
	host = "";
	path.clear();
	port = 0;
	existPort = false;
	existPath = true;
	long long port_tmp = 0;
	// Parsing scheme
	std::size_t delimiter = uriString.find(':');
	std::string	rest = uriString.substr(delimiter + 1);
	scheme = uriString.substr(0, delimiter);

	// Parsing host
	if ( rest.substr(0, 2) == "//")
	{
		std::size_t	authorityEnd = rest.find(splitchar, 2);
		if (authorityEnd == std::string::npos)
		{
			existPath = false;
			authorityEnd = rest.length();
		}
		std::size_t	portDelimeter = rest.find(":", 2);
		if (portDelimeter == std::string::npos)
		{
			if (existPath)
				host = rest.substr(2, authorityEnd - 2);
			else
				host = rest.substr(2);
		}
		else
		{
			host = rest.substr(2, portDelimeter - 2);
			if (rest.substr(portDelimeter + 1, authorityEnd - portDelimeter - 1).find_first_not_of("0123456789") != std::string::npos)
				return (false);
			port_tmp = (long long)atoi(rest.substr(portDelimeter + 1, authorityEnd - portDelimeter - 1).c_str());
			if (port_tmp == 0 && rest.substr(portDelimeter + 1, 1) != "0")
				return (false);
			if (port_tmp < 0 || port_tmp > 65535)
				return (false);
			port = (uint16_t)port_tmp;
			existPort = true;
		}
		rest = rest.substr(authorityEnd);
	}
	// Parsing Path
	while (!rest.empty() && existPath)
	{
		std::size_t	pathDelimiter = rest.find(splitchar);
		if (pathDelimiter == 0 && rest.length()== 1)
		{
			path.push_back(""); break ;
		}			
		else if (pathDelimiter == std::string::npos)
		{
			path.push_back(rest); break ;
		}
		else
			path.emplace_back(rest.begin(), rest.begin() + pathDelimiter);
		existPath = true;
		if (pathDelimiter + 1 == rest.length())
			path.push_back("");
		rest = rest.substr(pathDelimiter + splitchar.length());
	}
	return (true);
}

std::string	Uri::getScheme() const{
	return (scheme);
}

std::string	Uri::getHost() const{
	return (host);
}

std::vector<std::string> Uri::getPath(){
	return (path);
}

void	Uri::setSplitChar(std::string newchar){
	splitchar = newchar;
}

bool	Uri::hasPort() const{
	return (existPort);
}

bool	Uri::hasPath() const{
	return (existPath);
}

uint16_t	Uri::getPort() const{
	return (port);
}

// bool	Uri::isRelativeReference() const{

// }