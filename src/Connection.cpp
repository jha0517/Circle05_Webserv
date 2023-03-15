/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 12:05:16 by hyunah           ###   ########.fr       */
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
	Request		*request;
	char		buffer[BUFFSIZE];

	recv(server.clientfd, buffer, 3000, 0);
	request = server.parseResquest(buffer, messageEnd);
	bzero(buffer, sizeof(buffer));
	if (request == NULL)
		return "";
	std::cout << "Request Received : Socket[" << server.clientfd << "] Methode=<" << request->method << "> URI=<" << request->target.generateString() << ">" << std::endl;
	if (request->method == "GET")
		responseStr = response.getMethod(server, request, messageEnd);
	else if (request->method == "POST")
		responseStr = response.postMethod(server, request, messageEnd);
	else if (request->method == "DELETE")
		responseStr= response.deleteMethod(server, request, messageEnd);
	else
		return (NULL);
	return (responseStr);
}

// void Connection::setDataReceivedDelegate(DataReceivedDelegate newDataReceivedDelegate){
// 	dataReceivedDelegate = newDataReceivedDelegate;
// }
// void Connection::setBrokenDelegate(BrokenDelegate newBrokenDelegate){
// 	brokenDelegate = newBrokenDelegate;
// }
// void Connection::breakConnection(bool clean){
// 	(void) clean;
// }

// void Connection::sendData(std::vector<unsigned char> data){
// 	dataReceived.insert(dataReceived.end(), data.begin(), data.end());
// 	// for (std::vector<unsigned char>::iterator it = dataReceived.begin(); it != dataReceived.end(); ++it)
// 	// {
// 	// 	std::cout << *it;
// 	// }
// }

