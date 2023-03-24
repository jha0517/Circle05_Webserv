/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:52:00 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/24 16:00:06 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ServerManager.hpp"

ServerManager::ServerManager()
{
}


ServerManager::~ServerManager()
{
}

bool ServerManager::initiate(Config & config){
	servers = config.servers;
	error = false;

	this->log.printInit();
	FD_ZERO(&currentSockets);
	for (std::vector<Server *>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		if ((*it)->startListen() < 0)
		{
			error = true;
			this->log.printServerCreation(false, (*it));
			return (false);
		}
		this->log.printServerCreation(true, (*it));
		serverFds.push_back((*it)->sockfd);
		FD_SET((*it)->sockfd, &currentSockets);
	}
	return (true);
}

Server	*findServer(int i, std::vector<Server *> servers, int & isForServer)
{
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
bool	g_run = 1;

void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Byeee!" << std::endl;
	g_run = 0;
	// exit(EXIT_SUCCESS);
}

bool	ServerManager::run(){
	int				isForServer;
	Server			*server;
	signal(SIGINT, signalHandler);

	if (error == true)
		return (false);
	while (g_run)
	{
		readySockets = currentSockets;
		if (select(FD_SETSIZE, &readySockets, NULL, NULL, NULL) <= 0)
		{
			if (!g_run)
			{
				for (std::vector<int>::iterator it = serverFds.begin(); it != serverFds.end(); ++it)
				{
					close(*it);
				}
				return (0);
			}
			std::cerr << "Error in Select" << std::endl;
			return (EXIT_FAILURE);
		}
		for (int i = 0; i < FD_SETSIZE; i++)
		{
			if (FD_ISSET(i, &readySockets)){
				server = findServer(i, servers, isForServer);
				if (server && isForServer)
				{
					server->clientfd = server->acceptConnection();
					if (server->clientfd < 0)
						return (EXIT_FAILURE);
					FD_SET(server->clientfd, &currentSockets);
				}
				else if (server && (isForServer == 0))
				{
					server->newConnection();
					FD_CLR(i, &currentSockets);
				}
			}
		}
	}
	if (!g_run)
	{
		for (std::vector<int>::iterator it = serverFds.begin(); it != serverFds.end(); ++it)
		{
			close(*it);
		}
	}
	return (0);
}