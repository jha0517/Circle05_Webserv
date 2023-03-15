/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 19:15:26 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/ServerManager.hpp"
#include <csignal>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signalHandler);

	(void)			av;
	(void)			env;
	std::vector<int> serverFds;
	ServerManager	serverManager;
	Config			config;
	
//config Start
	std::vector<Server *> servers;
	Server			server1;
	Server			server2;
	server1.port = 8000;
	server1.host = "127.0.0.1";
	server1.root = "/home/hyunah/Documents/webserv/data";
	server1.serverName = "RatatouilleServer1";
	server1.locationRoot = "/fruits";
	server1.error_page = "/home/hyunah/Documents/webserv/data/error_pages";
	server1.maxClientBodySize = 400;

	servers.push_back(&server1);

	server2.port = 8001;
	server2.host = "127.0.0.1";
	server2.root = "/home/hyunah/Documents/webserv/data";
	server2.serverName = "RatatouilleServer2";
	server2.error_page = "/home/hyunah/Documents/webserv/data/error_pages";
	server2.locationRoot = "/fruits";
	server2.maxClientBodySize = 400;

	servers.push_back(&server2);
//config End

	config.servers = servers;
	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (EXIT_FAILURE);
	}

	serverManager.initiate(config);
	serverManager.run();
   return (EXIT_SUCCESS);
}

// std::string	checkFileAndGetContent(char *filename)
// {
// 	std::string		src;
// 	std::string		rawRequest;
// 	std::ifstream	ifs;
// 	char	c;
	
// 	ifs.open(filename);
// 	if (ifs.fail())
// 	{
// 		std::cerr << "Error : File opening failed." << std::endl;
// 		return (NULL);
// 	}
// 	while (ifs.get(c))
// 		src+= c;
// 	ifs.close();
// 	return (src);
// }

// bool	formatcheck(char *configFile)
// {
// 	std::string	str;

// 	str = checkFileAndGetContent(configFile);
// 	if (!checkBalancedParantheses(str))
// 		throw ServerManager::errorMsg("Error : Config file Parantheses not balanced\n");
// 	return (true);
// }
