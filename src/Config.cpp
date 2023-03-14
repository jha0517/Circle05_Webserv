/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:30:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 16:21:52 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Config.hpp"

Config::Config(/* args */)
{
}

Config::~Config()
{
}



bool	Config::parseFromString(const std::string &rawMsg){
	std::size_t	blockTerminator;
	std::string	rest;
	std::string endl = "\n";

	blockTerminator = rawMsg.find(endl);
	if (blockTerminator != std::string::npos)
		rest = rawMsg;
	while (blockTerminator != std::string::npos)
	{
		rest = rest.substr(blockTerminator + endl.length());

		std::cout << rest;
		blockTerminator = rest.find(endl);	
	}
	return (true);
}

int	Config::getServerSize(){
	return (servers.size());
}
