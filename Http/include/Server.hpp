/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/08 10:52:50 by hyunah           ###   ########.fr       */
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
	Uri				target;
	MessageHeaders	headers;
};

class Server
{
public:
	Server();
	~Server();
	Request	*parseResquest(const std::string &rawRequest);
	bool	mobilize(ServerTransport *transport, uint16_t port);
	void	demobilize();
	void	newConnection(Connection * newConnection);
	void	dataReceived(Connection *connection, std::vector<uint8_t> data);

private:
	Request					request;
	ServerTransport			*transport;
	std::set<Connection *>	activeConnections;
};

#endif
