/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/17 11:30:37 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include "../include/ServerManager.hpp"

Connection::Connection() : dataReceivedDelegate(NULL)
{
}

Connection::Connection(int new_socketfd) : socketfd(new_socketfd)
{
}

Connection::~Connection()
{
}

#define BUFFSIZE 3000

std::string	Connection::constructResponse(Server & server){
	std::string	responseStr;
	std::size_t	messageEnd;
	Response	response;
	Request		request;
	char		buffer[BUFFSIZE];
	ServerManager	*manag;
	
	manag = (ServerManager	*)server.manager;

	recv(server.clientfd, buffer, BUFFSIZE, 0);
	if (!request.parseResquest(buffer, messageEnd))// Bad Request -> error 400.
	{
		std::cout << "request parse Failed.\n";
		return (response.buildErrorResponse(server.error_page, 400));
	}
	if (request.protocol != "HTTP/1.1")
		return (response.buildErrorResponse(server.error_page, 505));
	manag->log.printRequest(server.clientfd, request.method, request.target.generateString());
	printf("%s", buffer);
	bzero(buffer, sizeof(buffer));

	if (request.method == "GET")
		responseStr = response.getMethod(server, &request, messageEnd);
	else if (request.method == "POST")
		responseStr = response.postMethod(server, &request, messageEnd);
	else if (request.method == "DELETE")
		responseStr= response.deleteMethod(server, &request, messageEnd);
	else
		return (response.buildErrorResponse(server.error_page, 500));
	return (responseStr);
}
