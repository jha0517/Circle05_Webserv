/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/07 10:34:33 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

Server::Server() : transport(nullptr)
{
}

Server::~Server()
{
	demobilize();
}

bool	parseRequestLine(Request *request, const std::string requestLine)
{
	//parse the method
	std::size_t	methodDelimiter = requestLine.find(' ');
	if (methodDelimiter == std::string::npos)
		return (false);
	request->method = requestLine.substr(0, methodDelimiter);

	//parse the target URI
	std::size_t	targetDelimiter = requestLine.find(' ', methodDelimiter + 1);
	request->target.parsingFromString(requestLine.substr(methodDelimiter + 1, targetDelimiter - methodDelimiter - 1));
	// //parse the protocol
	std::string protocol = requestLine.substr(targetDelimiter + 1);
	return (protocol == "HTTP/1.1");
}

Request*	Server::parseResquest(const std::string &rawRequest ){
	std::string	CRLF = "\r\n";
	std::size_t	requestLineEnd	= rawRequest.find(CRLF);
	
	if (requestLineEnd == std::string::npos)
		return (nullptr);
	std::string	requestLine = rawRequest.substr(0, requestLineEnd);
	if (!parseRequestLine(&request, requestLine))
		return (nullptr);
	if (!request.headers.parseFromString(rawRequest.substr(requestLineEnd + CRLF.length())))
		return (nullptr);
	if (request.headers.hasHeader("Content-Length"))
	{
		std::size_t	contentLength = atoi(request.headers.getHeaderValue("Content-Length").c_str());
		if (contentLength > request.headers.getBody().length())
			return (nullptr);
		else
		{
			std::string newBody = request.headers.getBody().substr(0, contentLength);
			request.headers.setBody(newBody);
		}
	}
	return (&request);
}

bool	Server::mobilize(ServerTransport *newTransport, uint16_t newPort){

	Connection newConnection;
	transport = newTransport;
	if (!transport->bindNetwork(newPort, &newConnection))
		return (false);
	return (true);
}

void	Server::demobilize(){
	
	std::cout << "server demobilizing..." << std::endl;
	if (transport != nullptr)
	{
		std::cout << "RELEASING TRANSPORT" << std::endl;
		transport->releaseNetwork();
		// transport->bound = false;
	}
	std::cout << "NO TRANSPORT" << std::endl;

	// transport = nullptr;
}
