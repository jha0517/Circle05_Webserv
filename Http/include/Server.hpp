/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/07 10:13:23 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <string>
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

private:
	Request	request;
	ServerTransport	*transport;
};

#endif
