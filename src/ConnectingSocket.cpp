/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectingSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:44:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 14:50:04 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ConnectingSocket.hpp"


ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface) : SimpleSocket(domain, service, protocol, port, interface)
{
	std::cout << "ConnectingSocket Contructor Called" << std::endl;

}

ConnectingSocket::~ConnectingSocket(void)
{
	std::cout << "ConnectingSocket Destructor Called" << std::endl;
}