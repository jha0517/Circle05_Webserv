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
ServerTransport::ServerTransport()
{
}

ServerTransport::~ServerTransport()
{
}

bool	ServerTransport::bindNetwork(uint16_t port, Connection *newConnectionDelegate){
	bound = true;
	return (true);
}

void	ServerTransport::releaseNetwork(){
	bound = false;
}
