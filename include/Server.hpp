/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 08:14:33 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <string>
# include <set>
# include "Connection.hpp"
# include <csignal>
# include <iostream>
# include "Webserv.hpp"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>

class Server
{
public:
	Server();
	~Server();
	Request	*parseResquest(const std::string &rawRequest);
	Request	*parseResquest(const std::string &rawRequest, size_t & messageEnd);
	int		startListen(std::string ipAddress, unsigned short port);
	int		startListen();
	int		acceptConnection(int sockfd, sockaddr_in & clientAddr);
	int		acceptConnection();
	void	demobilize();
	void	newConnection(int newSocket, sockaddr_in & clientAddr);
	void	newConnection();
	int						port;
	int						sockfd;
	int						clientfd;
	std::string				host;
	std::string				root;
	std::string				serverName;
	std::string				locationRoot;

private:
	Request					request;

	// std::set<Connection *>	activeConnections;
	struct sockaddr_in		serverAddr;
	struct sockaddr_in		clientAddr;

};

#endif
