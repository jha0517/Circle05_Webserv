/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 08:47:26 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
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
#include "main.h"

#define PORT1 8000
#define PORT2 8001


void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

std::vector<Server *> & manuelSetup(std::vector<Server *> & servers)
{
	Server server1;
	
	server1.port = 8000;
	server1.host = "127.0.0.1";
	server1.root = "/home/hyunah/Desktop/mysite";
	server1.serverName = "RatatouilleServer1";
	server1.locationRoot = "/fruits";

	servers.push_back(&server1);

	Server server2;
	
	server2.port = 33;
	server2.host = "127.0.0.1";
	server2.root = "/home/hyunah/Desktop/mysite";
	server2.serverName = "RatatouilleServer2";
	server2.locationRoot = "/fruits";

	servers.push_back(&server2);
	return (servers);
}

Server	*findServer(int i, std::vector<Server *> servers, int & isForServer)
{
	// for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
	// {
	// 	if (it->sockfd == i)
	// 		return (it);
	// }
	// return (NULL);
	std::vector<Server *>::iterator itS = servers.begin();
	std::vector<Server *>::iterator itE = servers.end();
	while (itS != itE)
	{
		if ((*itS)->sockfd == i)
		{
			isForServer = 1;
			return (*itS);
		}
		itS++;
	}
	itS = servers.begin();
	while (itS != itE)
	{
		if ((*itS)->clientfd == i)
		{
			isForServer = 0;
			return (*itS);
		}
		itS++;
	}
	return (NULL);
}
int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signalHandler);

	(void)			av;
	(void)			env;
	Server			*server;
	Server			server1;
	Server			server2;
	int				clientSocket;
	int				isForServer;
	sockaddr_in		clientAddr;
	fd_set			currentSockets, readySockets;
	std::vector<int> serverFds;

//config Start
	std::vector<Server *> servers;
	server1.port = 8000;
	server1.host = "127.0.0.1";
	server1.root = "/home/hyunah/Desktop/mysite";
	server1.serverName = "RatatouilleServer1";
	server1.locationRoot = "/fruits";

	servers.push_back(&server1);

	server2.port = 8001;
	server2.host = "127.0.0.1";
	server2.root = "/home/hyunah/Desktop/mysite";
	server2.serverName = "RatatouilleServer2";
	server2.locationRoot = "/fruits";

	servers.push_back(&server2);
//config End

	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (EXIT_FAILURE);
	}

	FD_ZERO(&currentSockets);
	for (std::vector<Server *>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		if ((*it)->startListen() < 0)
			return (printf("startListening Function Failed\n"), EXIT_FAILURE);
		FD_SET((*it)->sockfd, &currentSockets);
	}
	printf("Loop end\n");
	while (true)
	{
		readySockets = currentSockets;
		if (select(FD_SETSIZE, &readySockets, NULL, NULL, NULL) <= 0)
		{
			std::cerr << "Select Error" << std::endl;
			return (EXIT_FAILURE);
		}
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &readySockets)){
				server = findServer(i, servers, isForServer);
				std::cout << "IsForServer : "<< isForServer << std::endl;
				if (server && isForServer)
				{
					server->clientfd = server->acceptConnection();
					if (server->clientfd < 0)
						return (EXIT_FAILURE);
					FD_SET(server->clientfd, &currentSockets);
					printf("clientSocket: %d\n", server->clientfd);
				}
				else if (server && (isForServer == 0))
				{
					printf("New Connection!\n");
					server->newConnection();
					FD_CLR(i, &currentSockets);
				}
			}
		}
	}
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
