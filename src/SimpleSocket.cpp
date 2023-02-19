/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:16:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 13:29:33 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SimpleSocket.hpp"

SimpleSocket::SimpleSocket(int domain,int service, int protocol, int port, u_long interface){
	std::cout << "SimpleSocket Contructor Called" << std::endl;
	address.sin_family = domain;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(interface);
	connection = socket(domain, service, protocol);
}

SimpleSocket::~SimpleSocket(void)
{
	std::cout << "SimpleSocket Destructor Called" << std::endl;
}
