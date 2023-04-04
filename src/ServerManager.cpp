/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:52:00 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/04 10:53:27 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ServerManager.hpp"
bool	g_run = 1;

ServerManager::ServerManager() : error(0), servBlockCount(0), commonRoot("./"), commonDefaultErrorPage("./data/error_pages"), commonAutoIndex(false)
{}

ServerManager::~ServerManager(){}

ServerManager::ServerManager(ServerManager const & src){*this = src;}

ServerManager & ServerManager::operator=(ServerManager const & rhs){
	if (this != &rhs)
	{
		this->currentSockets = rhs.currentSockets;
		this->readySockets = rhs.readySockets;
		this->servers = rhs.servers;
		this->serverFds = rhs.serverFds;
		this->error = rhs.error;
		this->servBlockCount = rhs.servBlockCount;
	}
	return (*this);
}

unsigned int	ServerManager::getServerBlockCount(void) const{return (this->servBlockCount);}
void	ServerManager::setServerBlockCount(int i){this->servBlockCount = i;}
void	ServerManager::setRoot(std::string root){
	this->commonRoot = root;
	}
void	ServerManager::setAutoIndex(bool autoindex){this->commonAutoIndex = autoindex;}
void	ServerManager::setDefaultErrorPage(std::string dir){this->commonDefaultErrorPage = dir;}


void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Byeee!" << std::endl;
	g_run = 0;
}

bool ServerManager::initiate(){
	error = false;

	this->log.printInit();
	FD_ZERO(&currentSockets);
	for (std::vector<Server *>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		if ((*it)->startListen() < 0)
		{
			error = true;
			this->log.printServerCreation(false, (*it));
			this->closeAndFreeMem();
			return (false);
		}
		this->log.printServerCreation(true, (*it));
		serverFds.push_back((*it)->sockfd);
		FD_SET((*it)->sockfd, &currentSockets);
		this->max_socket_so_far = (*it)->sockfd;
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
			return ((*itS));
		}
		itS++;
	}
	itS = servers.begin();
	while (itS != itE)
	{
		if ((*itS)->clientfd == i)
		{
			isForServer = 0;
			return ((*itS));
		}
		itS++;
	}
	return (NULL);
}

int	ServerManager::closeAndFreeMem()
{
	for (std::vector<int>::iterator it = serverFds.begin(); it != serverFds.end(); ++it)
		close(*it);

	for (std::vector<Server *>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		for (std::set<Server::LocationBlock *>::iterator locit = (*it)->locationBloc.begin();\
		locit != (*it)->locationBloc.end(); ++locit)
			delete (*locit);
		for (std::set<Server::RedirectBlock *>::iterator reit = (*it)->redirectionBloc.begin();\
		reit != (*it)->redirectionBloc.end(); ++reit)
			delete (*reit);

		delete (*it);
	}
	return (0);
}

bool	ServerManager::run(){
	int				isForServer;
	Server			*server;
	struct timeval  timeout;
	signal(SIGINT, signalHandler);

	if (error == true)
		return (false);
	timeout.tv_sec  = 3;
	timeout.tv_usec = 0;
	while (g_run)
	{
		readySockets = currentSockets;
		int selectRet = select(this->max_socket_so_far + 1, &readySockets, NULL, NULL, &timeout);
		if ( selectRet < 0)
		{
			if (!g_run)
				return (closeAndFreeMem());
			log.printError("Error in Select");
			return (EXIT_FAILURE);
		}
		if ( selectRet == 0)
		{
			if (!g_run)
				return (closeAndFreeMem());
			log.printError("Timeout");
			return (EXIT_FAILURE);
		}
		for (int i = 0; i < this->max_socket_so_far + 1 && selectRet > 0; i++)
		{
			if (FD_ISSET(i, &readySockets)){
				server = findServer(i, servers, isForServer);
				if (server && isForServer)
				{
					server->clientfd = server->acceptConnection();
					if (server->clientfd < 0)
						return (EXIT_FAILURE);
					FD_SET(server->clientfd, &currentSockets);
					if (server->clientfd > this->max_socket_so_far)
						this->max_socket_so_far = server->clientfd;
				}
				else if (server && (isForServer == 0))
				{
					server->newConnection();
					FD_CLR(i, &currentSockets);
				}
			}
		}
	}
	return (0);
}

void	ServerManager::setCommonParameter(std::string root, bool autoindex, std::string defaultErrorPage){
	this->commonRoot = root;
	this->commonAutoIndex = autoindex;
	this->commonDefaultErrorPage = defaultErrorPage;
}

void	ServerManager::addServerBlock(){
	Server *sv = new Server();

	sv->root = this->commonRoot;
	sv->error_page = "./data/error_pages";
	sv->autoIndex = this->commonAutoIndex;
	sv->manager = this;
	this->servers.push_back(sv);
}
