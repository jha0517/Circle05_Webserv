/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/16 22:07:39 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"


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

	recv(server.clientfd, buffer, 3000, 0);
	if (!request.parseResquest(buffer, messageEnd))// Bad Request -> error 400.
		return (response.buildErrorResponse(server.error_page, 400));
	bzero(buffer, sizeof(buffer));
	if (request.protocol != "HTTP/1.1")
		return (response.buildErrorResponse(server.error_page, 505));
	std::cout << "Request Received : Socket[" << server.clientfd << "] Methode=<" << request.method << "> URI=<" << request.target.generateString() << ">" << std::endl;
	if (request.method == "GET")
		responseStr = response.getMethod(server, &request, messageEnd);
	else if (request.method == "POST")
		responseStr = response.postMethod(server, &request, messageEnd);
	else if (request.method == "DELETE")
		responseStr= response.deleteMethod(server, &request, messageEnd);
	else
		return (NULL);
	return (responseStr);
}
