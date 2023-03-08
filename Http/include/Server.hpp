/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/08 17:13:10 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <string>
# include <set>
# include "../../Url/include/Uri.hpp"
# include "../../MessageHeaders/include/MessageHeaders.hpp"
# include "ServerTransport.hpp"

struct	Request{
	std::string		method;
	std::string		body;
	Uri				target;
	MessageHeaders	headers;
};

struct ConnectionState
{
	Connection *connection;
	std::string	reassembleBuffer;
};

class Server
{
public:
	Server();
	~Server();
	Request	*parseResquest(const std::string &rawRequest);
	Request	*parseResquest(const std::string &rawRequest, size_t & messageEnd);
	bool	mobilize(ServerTransport *transport, uint16_t port);
	void	demobilize();
	void	newConnection(Connection * newConnection);
	void	dataReceived(ConnectionState *connection, std::vector<uint8_t> data);

private:
	Request					request;
	ServerTransport			*transport;
	std::set<ConnectionState *>	activeConnections;
};

#endif
