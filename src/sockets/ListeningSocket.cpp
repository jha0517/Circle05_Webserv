/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:59:14 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 15:26:14 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ListeningSocket.hpp"


ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg) : BindingSocket(domain, service, protocol, port, interface)
{
	// std::cout << "ListeningSocket Contructor Called" << std::endl;
	backlog = bklg;
	listening = startListening(getSocket(), backlog);
}

ListeningSocket::~ListeningSocket(void)
{
	// std::cout << "ListeningSocket Destructor Called" << std::endl;
}

int	ListeningSocket::connectToNetwork(int sock, struct sockaddr_in address){
	connection = connect(sock, (struct sockaddr *)&address, sizeof(address));
	testConnection(connection);
	return (connection);
}


int	ListeningSocket::startListening(int sock, int backlg){
	listening = listen(sock, backlg);
	testConnection(listening);
	return (listening);
}
