/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectingSocket.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:44:52 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 14:53:47 by hyunah           ###   ########.fr       */
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

int	ConnectingSocket::connectToNetwork(int sock, struct sockaddr_in address){
	connection = connect(sock, (struct sockaddr *)&address, sizeof(address));
	testConnection(connection);
	return (connection);
}
