/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:08:42 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 14:43:19 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BindingSocket.hpp"

BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface) : SimpleSocket(domain, service, protocol, port, interface)
{
	std::cout << "BindingSocket Contructor Called" << std::endl;
}

BindingSocket::~BindingSocket(void)
{
	std::cout << "BindingSocket Destructor Called" << std::endl;
}

int	BindingSocket::connectToNetwork(int sock, struct sockaddr_in address){
	connection = bind(sock, (struct sockaddr *)&address, sizeof(address));
	testConnection(connection);
	return (connection);
}
