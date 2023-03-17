/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/17 23:16:32 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include "../include/ServerManager.hpp"
#include <sys/stat.h>

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

std::string	Connection::constructResponse(Server & server, int & statusCode){
	std::string		responseStr;
	std::size_t		messageEnd;
	Response		response;
	Request			request;
	char			buffer[BUFFSIZE];
	ServerManager	*manag;
	bool			parsed;
	
	manag = (ServerManager	*)server.manager;

	// recv enought to know the content-length and for the body-> store in the vector<char>
	
	if (recv(server.clientfd, buffer, BUFFSIZE, 0) < 0)
	{
		std::cout << "request receiving Failed.\n";
		statusCode = 404;
		return (response.buildErrorResponse(server.error_page, 404));
	}
	
	parsed = request.parseResquest(buffer, messageEnd);
	manag->log.printRequest(server.clientfd, request.method, request.target.generateString());
	printf("%s", buffer);
	bzero(buffer, sizeof(buffer));

	// Bad Request parsing failed.-> error 400.
	if (!parsed)
	{
		std::cout << "request parse Failed.\n";
		statusCode = 400;
		return (response.buildErrorResponse(server.error_page, 400));
	}
	// Not allowed Method
	if (server.allowedMethod.find(request.method) == server.allowedMethod.end())
	{
		statusCode = 405;
		std::cout << "Not allowed Method.\n";
		return (response.buildErrorResponse(server.error_page, 405));
	}
	// Not supported Protocol
	if (request.protocol != "HTTP/1.1")
	{
		statusCode = 505;
		std::cout << "Protocol not supported.\n";
		return (response.buildErrorResponse(server.error_page, 505));
	}
	// Check URI exist if not 404 error. if yes. check Access is ok, if not, 403 error.
	if (!checkURIexist(server.findMatchingUri(request.target.generateString())))
	{
		statusCode = 404;
		std::cout << "Non existing URI .\n";
		return (response.buildErrorResponse(server.error_page, 404));
	}
	if (!checkURIaccess(request.target.generateString(), request.method))
	{
		statusCode = 404;
		std::cout << "URI not accessible.\n";
		return (response.buildErrorResponse(server.error_page, 404));
	}

	// build response
	if (request.method == "GET")
		responseStr = response.getMethod(server, &request, messageEnd, statusCode);
	else if (request.method == "POST")
		responseStr = response.postMethod(server, &request, messageEnd, statusCode);
	else if (request.method == "DELETE")
		responseStr= response.deleteMethod(server, &request, messageEnd, statusCode);
	else
		return (response.buildErrorResponse(server.error_page, 500));
	return (responseStr);
}
