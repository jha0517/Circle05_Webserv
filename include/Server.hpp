/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 08:48:01 by hyunah           ###   ########.fr       */
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
	int		startListen(std::string ipAddress, unsigned short port);
	int		acceptConnection();
	void	demobilize();
	void	newConnection(int newSocket);

private:
	Request					request;
	int						sockfd;
	int						clientfd;
	std::set<Connection *>	activeConnections;
	struct sockaddr_in		clientAddr;

};

#endif
