/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:27:35 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 16:33:04 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESERVER_H
# define SIMPLESERVER_H
# include "../../include/webserv.hpp"

class SimpleServer
{
private:
	int				connection;
	SimpleServer(void);
	ListeningSocket *socket;
	virtual	void	accepter(void) = 0;
	virtual	void	handler(void) = 0;
	virtual	void	responder(void) = 0;

public:
	SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg);
	~SimpleServer(void);
	virtual void launch(void) = 0;
	ListeningSocket *getListeningSocket(void);
};

#endif