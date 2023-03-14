/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 18:31:19 by hyunah           ###   ########.fr       */
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

#define PORT1 8000
#define PORT2 8001


void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

// void	manuelSetup(std::vector<Server *> servers)
// {
// 	servers.
// }
int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signalHandler);

	(void)			av;
	(void)			env;
	Server			server;
	int				clientSocket;
	int				serverSocket1;
	int				serverSocket2;
	sockaddr_in		clientAddr;
	fd_set			currentSockets, readySockets;
	std::vector<Server *> server;

	// manuelSetup(server);

	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (EXIT_FAILURE);
	}

	serverSocket1 = server.startListen("127.0.0.1", PORT1);
	if (serverSocket1 < 0)
		return (EXIT_FAILURE);

	serverSocket2 = server.startListen("127.0.0.1", PORT2);
	if (serverSocket1 < 0)
		return (EXIT_FAILURE);


	FD_ZERO(&currentSockets);
	FD_SET(serverSocket1, &currentSockets);
	FD_SET(serverSocket2, &currentSockets);

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
				if (i == serverSocket1 || i == serverSocket2)
				{
					clientSocket = server.acceptConnection(i, clientAddr);
					if (clientSocket < 0)
						return (EXIT_FAILURE);
					FD_SET(clientSocket, &currentSockets);
					printf("clientSocket: %d\n", clientSocket);
				}
				else
				{
					printf("New Connection!\n");
					server.newConnection(i, clientAddr);
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
