/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:52:00 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/05 11:29:10 by hyunah           ###   ########.fr       */
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
	FD_ZERO(&this->readSockets);
	FD_ZERO(&this->writeSockets);
	
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
		std::cout << "Server adding " << (*it)->sockfd << " readSockets" << std::endl;
		addToSet((*it)->sockfd, this->readSockets);
		this->max_socket_so_far = (*it)->sockfd;
	}
	return (true);
}

Server	*findServer(int i, std::vector<Server *> servers)
{
	std::vector<Server *>::iterator itS = servers.begin();
	std::vector<Server *>::iterator itE = servers.end();
	while (itS != itE)
	{
		if ((*itS)->sockfd == i)
			return ((*itS));
		itS++;
	}
	return (NULL);
}

Server	*findClient(int i, std::vector<Server *> servers)
{
	std::vector<Server *>::iterator itS = servers.begin();
	std::vector<Server *>::iterator itE = servers.end();
	while (itS != itE)
	{
		if ((*itS)->clientfd == i)
			return ((*itS));
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

void	ServerManager::addToSet(const int i, fd_set &set)
{
	FD_SET(i, &set);
	std::cout << "adding " << i << std::endl;
	if (i > this->max_socket_so_far)
		this->max_socket_so_far = i;
}

void    ServerManager::closeConnection(const int i)
{
    if (FD_ISSET(i, &this->writeSockets))
	{
		std::cout << "closing from writing " << i << std::endl;
        removeFromSet(i, this->writeSockets);
	}
    if (FD_ISSET(i, &this->readSockets))
	{
		std::cout << "closing from reading " << i << std::endl;
        removeFromSet(i, this->readSockets);
	}
    close(i);	
}

void	ServerManager::removeFromSet(const int i, fd_set &set)
{
    FD_CLR(i, &set);
	std::cout << "removing " << i << std::endl;
    if (i == this->max_socket_so_far)
        this->max_socket_so_far--;
}

bool	ServerManager::run(){
	Server			*server;
	struct timeval  timeout;
    fd_set  readSocketsCopy;
    fd_set  writeSocketsCopy;

	signal(SIGINT, signalHandler);

	if (error == true)
		return (false);
	timeout.tv_sec  = 3 * 60;
	timeout.tv_usec = 0;

	while (g_run)
	{
		readSocketsCopy = this->readSockets;
		writeSocketsCopy = this->writeSockets;
		int selectRet = select(this->max_socket_so_far + 1, &readSocketsCopy, &writeSocketsCopy, NULL, &timeout);
		if (!g_run)
			break;
		if (selectRet < 0)
		{
			printf("selectRet : %i\n", selectRet);
			return (log.printError("Error in Select"), EXIT_FAILURE);
		}
		else if (selectRet == 0)
			return (log.printError("Timeout"), EXIT_FAILURE);
		for (int i = 0; i < this->max_socket_so_far + 1 && selectRet > 0; i++)
		{
			// std::cout << i << std::endl;
			if (FD_ISSET(i, &readSocketsCopy) && (server = findServer(i, servers)))
			{
				server->clientfd = server->acceptConnection();
				if (server->clientfd < 0)
					return (EXIT_FAILURE);
				addToSet(server->clientfd, this->readSockets);
			}
			else if (FD_ISSET(i, &readSocketsCopy) && (server = findClient(i, servers)))
			{
				server->readRequest(i);
			}
			else if (FD_ISSET(i, &writeSocketsCopy) && (server = findClient(i, servers)))
			{
				server->writeResponse(i);
				sleep(1);
				closeConnection(i);
			}
			// std::cout << "finished"<< std::endl;
		}
	}
	return (closeAndFreeMem());
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
