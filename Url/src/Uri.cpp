/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uri.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:10 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/08 14:53:12 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Uri.hpp"
#include <iostream>
#include <sstream>

Uri::Uri() : scheme (""), host(""), splitchar("/"), port(0), existPort(true), existPath(false)
{
}

Uri::~Uri()
{
}

bool	Uri::parsingFromString(const std::string & uriString){
	scheme = "";
	host = "";
	path.clear();
	port = 0;
	existPort = false;
	existPath = true;
	long long port_tmp = 0;
	
	// Parsing scheme
	std::size_t schemeDelimiter = uriString.find(':');
	std::string	rest;
	if (schemeDelimiter == std::string::npos)
	{
		rest = uriString;
	}
	else{
		rest = uriString.substr(schemeDelimiter + 1);
		scheme = uriString.substr(0, schemeDelimiter);
	}
	// Parsing host
	std::size_t	pathEnd = rest.find_first_of("?#");
	std::string	pathString;
	std::string	queryAndOrFrag;
	if (pathEnd == std::string::npos)
		pathString = rest;
	else
	{
		pathString = rest.substr(0, pathEnd);
		queryAndOrFrag = rest.substr(pathString.length());
	}
	if ( pathString.substr(0, 2) == "//")
	{
		std::size_t	authorityEnd = pathString.find(splitchar, 2);
		if (authorityEnd == std::string::npos)
		{
			existPath = false;
			authorityEnd = pathString.length();
		}
		std::size_t	portDelimeter = pathString.find(":", 2);
		if (portDelimeter == std::string::npos)
		{
			if (existPath)
				host = pathString.substr(2, authorityEnd - 2);
			else
				host = pathString.substr(2);
		}
		else
		{
			host = pathString.substr(2, portDelimeter - 2);
			if (pathString.substr(portDelimeter + 1, authorityEnd - portDelimeter - 1).find_first_not_of("0123456789") != std::string::npos)
				return (false);
			port_tmp = (long long)atoi(pathString.substr(portDelimeter + 1, authorityEnd - portDelimeter - 1).c_str());
			if (port_tmp == 0 && pathString.substr(portDelimeter + 1, 1) != "0")
				return (false);
			if (port_tmp < 0 || port_tmp > 65535)
				return (false);
			port = (uint16_t)port_tmp;
			existPort = true;
		}
		pathString = pathString.substr(authorityEnd);
	}
	// Parsing Path
	while (!pathString.empty() && existPath)
	{
		std::size_t	pathschemeDelimiter = pathString.find(splitchar);
		if (pathschemeDelimiter == 0 && pathString.length()== 1)
		{
			path.push_back(""); break ;
		}			
		else if (pathschemeDelimiter == std::string::npos)
		{
			path.push_back(pathString); break ;
		}
		else
			path.emplace_back(pathString.begin(), pathString.begin() + pathschemeDelimiter);
		existPath = true;
		if (pathschemeDelimiter + 1 == pathString.length())
			path.push_back("");
		pathString = pathString.substr(pathschemeDelimiter + splitchar.length());
	}

	std::size_t	fragschemeDelimiter = queryAndOrFrag.find('#');
	std::string	leftover;
	if (fragschemeDelimiter == std::string::npos)
	{
		fragment = "";
		leftover = queryAndOrFrag;
	}
	else
	{
		leftover = queryAndOrFrag.substr(0, fragschemeDelimiter);
		fragment = queryAndOrFrag.substr(fragschemeDelimiter + 1);
	}
	if (!leftover.empty())
		query = leftover.substr(1);
	return (true);
}

std::string	Uri::getScheme() const{
	return (scheme);
}

std::string	Uri::getFragement() const{
	return (fragment);
}

std::string	Uri::getQuery() const{
	return (query);
}

std::string	Uri::getHost() const{
	return (host);
}

std::vector<std::string> Uri::getPath(){
	return (path);
}

void	Uri::setSplitChar(const std::string & newchar){
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

bool	Uri::hasRelativeReference() const{

	return (scheme.empty());
}

bool	Uri::ContainsRelativePath() const{
	if (path.empty())
		return false;
	else
		return (path[0].empty());
}

void Uri::setScheme(const std::string & newScheme){
	scheme = newScheme;
}
void Uri::setHost(const std::string & newHost){
	host = newHost;
}
void Uri::setQuery(const std::string & newQuery){
	query = newQuery;
}

std::string	Uri::generateString(){
	std::ostringstream	buffer;

	if (!scheme.empty())
		buffer << scheme << ":";
	if (!host.empty())
		buffer << "//" << host;
	if (!path.empty())
	{
		if (path.size() == 1)
		{
			buffer << '/';
		}
		else
		{
			for (std::vector<std::string>::iterator it = path.begin() + 1; it != path.end(); ++it)
			{
				buffer << '/' << *it;
			}
		}
	}
	if (!query.empty())
		buffer << "?" << query;
	if (!fragment.empty())
		buffer << "#" << fragment;

	return (buffer.str());
}

Uri & Uri::operator=(const Uri &rhs){
	existPath = rhs.existPath;
	existPort = rhs.existPort;
	port = rhs.port;
	scheme = rhs.scheme;
	fragment = rhs.fragment;
	query = rhs.query;
	host = rhs.host;
	path = rhs.path;
	splitchar = rhs.splitchar;
	return (*this);
}

bool	Uri::operator==(Uri const &rhs) const {
	if (existPath != rhs.existPath)
		return (false);
	if (existPort != rhs.existPort)
		return (false);
	if (port != rhs.port)
		return (false);
	if (scheme != rhs.scheme)
		return (false);
	if (fragment != rhs.fragment)
		return (false);
	if (query != rhs.query)
		return (false);
	if (host != rhs.host)
		return (false);
	if (path != rhs.path)
		return (false);
	return (true);
}
