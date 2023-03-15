/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:30:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 19:12:00 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

Config::Config(/* args */)
{
}

Config::~Config()
{
}

// bool	checkBalancedParantheses(std::string s, std::size_t & blockEnd)
// {
// 	std::stack<char>par;
// 	(void) blockEnd;

// 	for (unsigned i = 0; i < s.size(); i++)
// 	{
// 		if (s[i] == '{')
// 			par.push(s[i]);
// 		else if (s[i] == '}')
// 		{
// 			if (s.empty() || par.top() != '{')
// 				return (false);
// 			else
// 			{	
// 				// std::cout << par.top() << std::endl;
// 				par.pop();
// 				// std::cout << s[i] << std::endl;
// 				// std::cout << par.empty() << std::endl;
// 			}
// 		}
// 	}
// 	// std::cout << "return : "<< par.empty() << std::endl;
// 	return (par.empty());
// }

// int	findBalencedParantheses(std::string raw, std::string keyword)
// {
// 	std::size_t	found;
// 	std::string	rest;
// 	(void) keyword;

// 	found = raw.find(keyword);
// 	if (found == std::string::npos)
// 		return (-1);
// 	rest = raw.substr(found + keyword.length());

// 	return (1);
// }

// bool	findBlock(std::string rest, std::string keyword, std::size_t & serverDelimiter, std::size_t & blockTerminator)
// {	
// 	serverDelimiter = rest.find("server");
// 	if (serverDelimiter == std::string::npos)
// 		return (false);
// 	rest = rest.substr(serverDelimiter);
// 	int start = 0;
// 	for (unsigned i = 0; i < rest.size(); i++)
// 	{
// 		if (rest[i] == '{')
// 			start++;
// 		if (rest[i] == '}')
// 		{
// 			start--;
// 			if (start == 0)
// 			{
// 				blockTerminator = i;
// 				return (true);
// 			}
// 		}
// 	}
// 	return (true);
// }

// bool	Config::parseFromString(const std::string &rawMsg){
// 	std::size_t	blockTerminator = std::string::npos;
// 	std::size_t	serverDelimiter;
// 	std::size_t	endlDelimiter;
// 	std::string	rest;
// 	std::string	serverBlockRest;
// 	std::string	serverBlock;

// 	if (!checkBalancedParantheses(rawMsg, blockTerminator))
// 		return (false);
// 	rest = rawMsg;
// 	while (findBlock(rest, "server", serverDelimiter, blockTerminator))
// 	{
// 		serverBlock = rest.substr(serverDelimiter, blockTerminator + 1);
// 		serversConfig.push_back(rest.substr(serverDelimiter, blockTerminator + 1));
// 		// serverBlockRest = serverBlock;
// 		// endlDelimiter = serverBlockRest.find(";");
// 		// while(endlDelimiter != std::string::npos){
			
// 		// 	std::cout << serverBlockRest.substr(0, endlDelimiter);
// 		// 	serverBlockRest = serverBlockRest.substr(endlDelimiter + 1);
// 		// 	endlDelimiter = serverBlockRest.find("\n");
// 		// }
// 		rest = rest.substr(blockTerminator + 1);
// 	}
// 	return (true);
// }

// int	Config::getServerCount(){
// 	return (serversConfig.size());
// }
