/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/04 10:31:22 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/ServerManager.hpp"
#include "../include/Connection.hpp"

Server::Server() : sockfd(-1), index("index.html"){
	std::set<std::string> extension;

	extension.insert(".php");
	this->cgiBloc.cgiPath = "./data/cgi-bin";
	this->cgiBloc.cgiScriptPath = "/usr/bin/cgi-bin";
	this->cgiBloc.cgiExt = extension;
}

Server::~Server(){}

Server::Server(Server const &src){*this = src;}

Server &Server::operator=(Server const &rhs){
	if(this != &rhs)
	{
		this->port = rhs.port;
		this->sockfd = rhs.sockfd;
		this->autoIndex = rhs.autoIndex;
		this->clientfd = rhs.clientfd;
		this->maxClientBodySize = rhs.maxClientBodySize;
		this->error_page = rhs.error_page;
		this->host = rhs.host;
		this->root = rhs.root;
		this->index = rhs.index;
		this->allowedMethod = rhs.allowedMethod;
		this->manager = rhs.manager;

		this->locationBloc = rhs.locationBloc;
		this->cgiBloc = rhs.cgiBloc;
		this->redirectionBloc = rhs.redirectionBloc;
	}
	return (*this);
}

void	Server::setUploadPath(std::string path){this->uploadPath = path;}
void	Server::setLocBlockCount(unsigned int i){this->nLoc = i;}
void	Server::setRedirectBlockCount(unsigned int i){this->nRedirect = i;}
void	Server::setPort(unsigned short i){this->port = i;}
void	Server::setHost(std::string str){this->host = str;}
void	Server::setMaxClientBodySize(unsigned int i){this->maxClientBodySize = i;}
void	Server::setIndex(std::string index){this->index = index;}
void	Server::setAllowedMethod(std::set<std::string> m){this->allowedMethod = m;}
void	Server::setCgiPath(std::string path){this->cgiBloc.cgiPath = path;}
void	Server::setCgiScriptPath(std::string path){this->cgiBloc.cgiScriptPath = path;}
void	Server::setCgiExt(std::set<std::string> extension){

	for(std::set<std::string>::iterator it = extension.begin(); it != extension.end(); ++it)
	{
		this->cgiBloc.cgiExt.insert(*it);
	}
}
unsigned int	Server::getLocBlockCount(){return (this->nLoc);}
unsigned int	Server::getRedirectBlockCount(){return (this->nRedirect);}

void	Server::addLocBlock(std::string dir, std::string index)
{
	LocationBlock *loc = new LocationBlock();
	loc->index = "index.html";

	loc->dir = dir;
	if (!index.empty())
		loc->index = index;
	this->locationBloc.insert(loc);
}

void	Server::addRedirectBlock(std::string dir, std::string ret)
{
	RedirectBlock	*rblock = new RedirectBlock();

	rblock->dir = dir;
	rblock->ret = ret;
	this->redirectionBloc.insert(rblock);
}

int	Server::startListen(){

	ServerManager *servManag;

	servManag = (ServerManager *)manager;
	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd < 0)
		return (servManag->log.printError("Error in Connection"), -1);

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(this->port);
	serverAddr.sin_addr.s_addr = inet_addr(this->host.c_str());

	if (bind(this->sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		return (servManag->log.printError("Error in binding"), -1);
	}
	if ((listen(this->sockfd, 10)) != 0)
	{
		return (servManag->log.printError("Error in Listening"), -1);
	}

	return (this->sockfd);
}

void	Server::newConnection(){
    std::vector<char> data;
	int			statusCode;
	Connection	connect(clientfd);
	ServerManager *servManag;

	servManag = (ServerManager *)manager;
	servManag->log.printConnection(inet_ntoa(clientAddr.sin_addr), clientfd);
	data = connect.constructResponse(*this, statusCode);

	size_t	size = data.size();
	int	numSent = 0;
	char	*p = static_cast<char *>(data.data());
	while (size > 0)
	{
		numSent = send(clientfd, p, size, 0);
		if (numSent < 0)
			return (servManag->log.printError("Sending message Failed"));
		size -= numSent;
	}
	servManag->log.printResponse(clientfd, statusCode);
	close(clientfd);
}

int	Server::acceptConnection(){
    int					addrlen = sizeof(clientAddr);
	
	clientfd = accept(sockfd, (struct sockaddr*)&clientAddr, (socklen_t *)&addrlen);
	if (clientfd < 0)
		return (-1);
	return (clientfd);
}
#include <sys/stat.h>

std::string	Server::findMatchingUri(std::string path){
	std::string indexfilename = "index.html";
	std::ifstream	ifs;

	if (path.find(".") != std::string::npos)
	{
		std::cout <<"1final path is " << this->root + path << std::endl;
		return (this->root + path);
	}
	if (path == "/")
	{
		indexfilename = this->index;
		std::cout <<"2final path is " << this->root + "/" + indexfilename << std::endl;
		return (this->root + "/" + indexfilename);
	}
	//check in LocationBlock
	std::set<LocationBlock *>::iterator it;
	for (std::set<LocationBlock *>::iterator it = this->locationBloc.begin(); it != this->locationBloc.end(); ++it)
	{
		std::cout << "Looping throuh...: " << (*it)->dir << " == ? "<< path << std::endl;
		if ((*it)->dir == path)
		{
			indexfilename = (*it)->index;
			std::cout <<"3final path is " << this->root + path  + "/" + indexfilename << std::endl;
			return (this->root + path  + "/" + indexfilename);
		}
	}

	//check in RedirectionBlock
	std::set<RedirectBlock *>::iterator ir;
	for (std::set<RedirectBlock *>::iterator ir = this->redirectionBloc.begin(); ir != this->redirectionBloc.end(); ++ir)
	{
		if (*((*ir)->dir).rbegin() == '/')
			(*ir)->dir.erase((*ir)->dir.size() - 1, 1);

		std::cout << "Looping throuh...: " << (*ir)->dir << " == ? "<< path << std::endl;
		std::cout << "Comparing :" << (*ir)->dir << " and " << path << std::endl;
		if ((*ir)->dir == path)
		{
			std::cout << "Match :" << (*ir)->dir << " and " << path << std::endl;
			return ((*ir)->ret);
			// std::cout <<"3final path is " << this->root + path  + "/" + indexfilename << std::endl;
			// return (this->root + path  + "/" + indexfilename);
		}
	}

	//check autoIndex for Directory .
	std::string tmp;
	tmp = this->root + path;
	std::cout << "checking if -"<< tmp <<"- exist" << std::endl;
	struct stat sb;
	if (stat(tmp.c_str(), &sb) == 0)
	{
		std::string tmp2 = tmp + "/" + indexfilename;
		std::cout << "The path is valid, index yes? " + tmp2+"\n";
		if (!check_filename_get_str(tmp2.c_str()).empty())
		{
			std::cout << "Index file Yes! Returning "<< tmp2 <<"\n";
			return (tmp2);
		}
		else
		{
			std::cout << "Index file No! Returning " << tmp <<"\n";
			return (tmp);
		}
	}
	else
		std::cout << "The path is NOT valid\n";

	std::string nul;
	std::cout << "Returning Null\n";
	return (nul);
}
