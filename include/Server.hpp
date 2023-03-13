/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/13 22:35:07 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <string>
# include <string.h>
# include <set>
# include "Uri.hpp"
# include "MessageHeaders.hpp"
# include "Connection.hpp"
# include <csignal>
# include <iostream>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>

struct	Request{
	std::string		method;
	std::string		body;
	Uri				target;
	MessageHeaders	headers;
};

// struct ConnectionState
// {
// 	Connection *connection = NULL;
// 	std::string	reassembleBuffer;
// };

class Server
{
public:
	Server();
	~Server();
	Request	*parseResquest(const std::string &rawRequest);
	Request	*parseResquest(const std::string &rawRequest, size_t & messageEnd);
	// bool	mobilize(ServerTransport *transport, unsigned short port);
	int		startListen(std::string ipAddress, unsigned short port);
	int		acceptConnection();
	void	demobilize();
	// void	newConnection(Connection * newConnection);
	void	newConnection(int newSocket, sockaddr_in newAddr, char *buffer);
	// void	dataReceived(ConnectionState *connection, std::vector<unsigned char> data);

private:
	Request					request;
	// ServerTransport			*transport;
	int						sockfd;
	std::set<Connection *>	activeConnections;
};

#endif
