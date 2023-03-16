/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/16 09:02:20 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Connection.hpp"

Server::Server() : sockfd(-1)
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

bool	parseSize(const	std::string & numberString, size_t	& number)
{
	const	char *str = numberString.c_str();
	number = 0;
	for (unsigned char i= 0; i < numberString.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		// detect overflow
		size_t previousNumber = number;
		number *= 10;
		number += (unsigned short)(str[i] - '0');
		if (number / 10 != previousNumber)
			return false;
	}
	return true;
}

Request*	Server::parseResquest(const std::string &rawRequest, size_t & messageEnd){
	std::string	CRLF = "\r\n";

	// parse the request line.
	std::size_t	requestLineEnd	= rawRequest.find(CRLF);	
	if (requestLineEnd == std::string::npos)
		return (NULL);
	std::string	requestLine = rawRequest.substr(0, requestLineEnd);
	if (!parseRequestLine(&request, requestLine))
		return (NULL);

	// parse the headers line.
	size_t	bodyOffset;
	size_t	headerOffset = requestLineEnd + CRLF.length();
	if (!request.headers.parseFromString(rawRequest.substr(headerOffset), bodyOffset))
		return (NULL);

	// check for content-length header. if present, use this to determine how many character should be in the body.
	bodyOffset += headerOffset;
	size_t	maxContentLength = rawRequest.length() - bodyOffset;
	size_t	contentLength;
	// extract body.
	if (request.headers.hasHeader("Content-Length"))
	{
		if (!parseSize(request.headers.getHeaderValue("Content-Length"), contentLength))
			return NULL;
		if (contentLength > maxContentLength)
			return NULL;
		else
		{
			request.body = rawRequest.substr(bodyOffset, contentLength);
			messageEnd = bodyOffset + contentLength + CRLF.length();
		}
	}
	else
	{
		request.body = rawRequest.substr(bodyOffset);
		messageEnd = rawRequest.length();
	}
	return (&request);
}
	
Request*	Server::parseResquest(const std::string &rawRequest){
	std::size_t	messageEnd;

	return (this->parseResquest(rawRequest, messageEnd));
}

int	Server::startListen(){

	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd < 0)
	{
		std::cout <<"Error in Connection\n" << std::endl;
		return (-1);
	}
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(this->port);
	serverAddr.sin_addr.s_addr = inet_addr(this->host.c_str());
	if (bind(this->sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		std::cerr <<"Error in binding\n" << std::endl;
		return (-1);
	}
	if ((listen(this->sockfd, 10)) != 0)
	{
		std::cerr <<"Error in Listening\n" << std::endl;
		return (-1);
	}
	return (this->sockfd);
}

void	Server::demobilize(){
}

void	Server::newConnection(){
	std::string	response;
	Connection	connect(clientfd);

	std::cout << "New Connection : \
	Host[" << inet_ntoa(clientAddr.sin_addr) <<"] \
	PORT[" << ntohs(clientAddr.sin_port) << "] \
	AssignedFd[" << clientfd << "]" << std::endl;
	response = connect.constructResponse(*this);
	printf("%s\n", response.c_str());
	if (send(clientfd, response.c_str(), strlen(response.c_str()), 0) < 0)
		std::cerr << "Sending message Failed" << std::endl;
}

int	Server::acceptConnection(){
    int					addrlen = sizeof(clientAddr);
	
	clientfd = accept(sockfd, (struct sockaddr*)&clientAddr, (socklen_t *)&addrlen);
	if (clientfd < 0)
		return (-1);
	return (clientfd);
}