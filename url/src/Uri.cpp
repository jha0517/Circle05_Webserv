
#include "../include/Uri.hpp"
#include <iostream>
Uri::Uri() : scheme (""), host(""), splitchar("/")
{
}

Uri::~Uri()
{
}

bool	Uri::ParsingFromString(const std::string & uriString){
	scheme = "";
	host = "";
	path.clear();
	std::size_t delimiter = uriString.find(':');
	std::string	rest = uriString.substr(delimiter + 1);
	scheme = uriString.substr(0, delimiter);
	if ( rest.substr(0, 2) == "//")
	{
		std::size_t	authorityEnd = rest.find(splitchar, 2);
		host = rest.substr(2, authorityEnd - 2);
		rest = rest.substr(authorityEnd);
	}

	// Parsing Path
	while (!rest.empty())
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

