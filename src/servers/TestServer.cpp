/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:27:37 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 16:55:50 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TestServer.hpp"
TestServer::TestServer(void) : SimpleServer(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10)
{
}

TestServer::~TestServer(void)
{
}

void	TestServer::accepter(void)
{
	struct	sockaddr_in	address = getListeningSocket()->getAddress();
	int addrlen = sizeof(address);
	int socket = getListeningSocket()->getSocket();
	new_socket = accept(socket, (struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (new_socket < 0)
	{
		perror("In accept");
		exit(EXIT_FAILURE);
	}
	read(new_socket, buffer, 30000);
}

void	TestServer::handler(void)
{
	std::cout << buffer << std::endl;
}

void	TestServer::responder(void)
{
	std::string	str = "Hello World!";
	write(new_socket, str.c_str(), strlen(str.c_str()));
	close(new_socket);
}

void	TestServer::launch(void)
{
	while (true)
	{
		std::cout << "================ WAITING ================ " << std::endl;
		accepter();
		handler();
		responder();
		std::cout << "================ DONE ================ " << std::endl;
	}
}