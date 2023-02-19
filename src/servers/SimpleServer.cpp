/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleServer.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:27:37 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 16:50:34 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleServer.hpp"

SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bklg)
{
	socket = new ListeningSocket(domain, service, protocol, port, interface, bklg);

}

SimpleServer::~SimpleServer()
{
	// delete socket;
}

ListeningSocket * SimpleServer::getListeningSocket(){
	return (socket);
}