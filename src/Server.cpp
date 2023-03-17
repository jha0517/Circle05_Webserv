/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/17 22:57:12 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/ServerManager.hpp"
#include "../include/Connection.hpp"

Server::Server() : sockfd(-1)
{
}

Server::~Server()
{
}

int	Server::startListen(){

	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd < 0)
	{
		std::cout <<"Error in Connection\n" << std::endl;
		return (-1);
	}
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(this->port);
	serverAddr.sin_addr.s_addr = inet_addr(this->host.c_str());
	if (bind(this->sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr <<"Error in binding\n" << std::endl;
		return (-1);
	}
	if ((listen(this->sockfd, 10)) != 0)
	{
		std::cerr <<"Error in Listening\n" << std::endl;
		return (-1);
	}
	return (this->sockfd);
}

void	Server::newConnection(){
	std::string	response;
	int			statusCode;
	Connection	connect(clientfd);
	ServerManager *servManag;

	servManag = (ServerManager *)manager;
	servManag->log.printConnection(inet_ntoa(clientAddr.sin_addr), clientfd);
	response = connect.constructResponse(*this, statusCode);
	if (send(clientfd, response.c_str(), strlen(response.c_str()), 0) < 0)
		std::cerr << "Sending message Failed" << std::endl;
	servManag->log.printResponse(clientfd, statusCode);
	printf("Response:\n%s\n", response.c_str());
}

int	Server::acceptConnection(){
    int					addrlen = sizeof(clientAddr);
	
	clientfd = accept(sockfd, (struct sockaddr*)&clientAddr, (socklen_t *)&addrlen);
	if (clientfd < 0)
		return (-1);
	return (clientfd);
}

std::string	Server::findMatchingUri(std::string path){
	std::string ret;
	std::string indexfilename = "index.html";

	if (path.find(".") != std::string::npos)
	{
		return (this->root + path);
	}
	if (path == "/")
	{
		indexfilename = this->index;
		std::cout <<"final path is " << this->root + "/" + indexfilename << std::endl;
		return (this->root + "/" + indexfilename);
	}

	std::map<std::string, std::string>::iterator itMap;
	std::set<LocationBlock *>::iterator it;
	for (std::set<LocationBlock *>::iterator it = this->locationBloc.begin(); it != this->locationBloc.end(); ++it)
	{
		itMap = (*it)->info.find("dir");
		std::cout << "Looping throuh...: " << itMap->second << std::endl;
		if (itMap->second == path)
		{
			itMap = (*it)->info.find("index");
			if (itMap != (*it)->info.end())
				indexfilename = itMap->second;
			std::cout <<"final path is " << this->root + path  + "/" + indexfilename << std::endl;
			return (this->root + path  + "/" + indexfilename);
		}
	}
	return (ret);
}
