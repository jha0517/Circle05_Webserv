/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerTransport.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/06 10:54:26 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ServerTransport.hpp"
#include <iostream>

void	testFunction(Connection *connection)
{
}

ServerTransport::ServerTransport() :bound(false), port(0), connectionDelegate(nullptr)
{
	this->setNewConnectionDelegate(&testFunction);
}

ServerTransport::~ServerTransport()
{
}

bool	ServerTransport::bindNetwork(uint16_t newPort, NewConnectionDelegate newConnectionDelegate){
	port = newPort;
	bound = true;
	connectionDelegate = newConnectionDelegate;
	return (true);
}

void	ServerTransport::releaseNetwork(){
	bound = false;
}

bool	ServerTransport::setNewConnectionDelegate(NewConnectionDelegate newConnectionDelegate){
	connectionDelegate = newConnectionDelegate;
	return (true);
}
