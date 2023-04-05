/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/05 00:53:32 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include "../include/ServerManager.hpp"
#include <sys/stat.h>

Connection::Connection(){}

Connection::Connection(int new_socketfd) : socketfd(new_socketfd){}

Connection::~Connection(){}

Connection::Connection(Connection const &src){
	*this = src;
}
Connection &Connection::operator=(Connection const &rhs){
	if (this != &rhs)
	{
		this->dataReceived = rhs.dataReceived;
		this->socketfd = rhs.socketfd;
	}
	return (*this);
}
// #define BUFFSIZE 3000

bool	checkURIexist(std::string path)
{
	struct stat sb;

	std::cout << "Checking if path exist : " << path << std::endl;
    if (stat(path.c_str(), &sb) == 0)
		return (true);
	return (false);
}

bool	checkURIaccess(std::string path, std::string method)
{
	(void) path;
	if (method == "GET")
	{
		
	}
	else if (method == "POST")
	{

	}
	else if (method == "DELETE")
	{

	}
	return (true);
}

std::vector<char>	Connection::constructResponse(Server & server, int & statusCode){
	std::string		responseStr;
	std::size_t		messageEnd;
	Response		response;
	
	// Not allowed Method
	if (server.allowedMethod.find(request->method) == server.allowedMethod.end())
	{
		statusCode = 405;
		std::cout << "Not allowed Method.\n";
		return (response.buildErrorResponse(server.error_page, 405));
	}
	// Not supported Protocol
	if (request->protocol != "HTTP/1.1")
	{
		statusCode = 505;
		std::cout << "Protocol not supported.\n";
		return (response.buildErrorResponse(server.error_page, 505));
	}
	// if (!checkURIaccess(request.target.generateString(), request.method))
	// {
	// 	statusCode = 404;
	// 	std::cout << "URI not accessible.\n";
	// 	return (response.buildErrorResponse(server.error_page, 404));
	// }
	// std::cout << "request.method : " << request.method << std::endl;

	// build response
	messageEnd = 0;
	if (request->method == "GET")
		dataReceived = response.getMethod(server, request, messageEnd, statusCode);
	else if (request->method == "POST")
	{
		// request.body = receivedData;
		dataReceived = response.postMethod(server, request, messageEnd, statusCode);
	}
	// else if (request.method == "DELETE")
		// responseStr= response.deleteMethod(server, &request, messageEnd, statusCode);
	else
		return (response.buildErrorResponse(server.error_page, 500));
	return (dataReceived);
}

void	Connection::setRequest(Request *req){
	this->request = req;
}
