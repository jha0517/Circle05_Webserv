/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/08 18:08:29 by hyunah           ###   ########.fr       */
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

bool	parseSize(const	std::string & numberString, size_t	& number)
{
	const	char *str = numberString.c_str();
	number = 0;
	for (int i= 0; i < numberString.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		// detect overflow
		size_t previousNumber = number;
		number *= 10;
		number += (uint16_t)(str[i] - '0');
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
		return (nullptr);
	std::string	requestLine = rawRequest.substr(0, requestLineEnd);
	if (!parseRequestLine(&request, requestLine))
		return (nullptr);

	// parse the headers line.
	size_t	bodyOffset;
	size_t	headerOffset = requestLineEnd + CRLF.length();
	if (!request.headers.parseFromString(rawRequest.substr(headerOffset), bodyOffset))
		return (nullptr);

	// check for content-length header. if present, use this to determine how many character should be in the body.
	bodyOffset += headerOffset;
	size_t	maxContentLength = rawRequest.length() - bodyOffset;
	size_t	contentLength;
	// extract body.
	if (request.headers.hasHeader("Content-Length"))
	{
		if (!parseSize(request.headers.getHeaderValue("Content-Length"), contentLength))
			return nullptr;
		if (contentLength > maxContentLength)
			return nullptr;
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

Server		*serv;
ConnectionState	*tmpConnection;

void	test(Connection *connection)
{
	// std::cout << "test called serv instance address " << serv << std::endl;
	serv->newConnection(connection);
}

bool	Server::mobilize(ServerTransport *newTransport, uint16_t newPort){

	transport = newTransport;
	serv = this;
	if(!transport->bindNetwork(newPort, test))
	{
		this->transport = nullptr;
		return false;		
	}
	return true;
}

void	Server::demobilize(){
	
	if (transport != nullptr)
		transport->releaseNetwork();
	transport = nullptr;
}

void	Server::dataReceived(ConnectionState *connectionState, std::vector<uint8_t> data){
	Request		*request;
	std::size_t	messageEnd;

	connectionState->reassembleBuffer += std::string(data.begin(), data.end());
	request = this->parseResquest(connectionState->reassembleBuffer, messageEnd);
	if (request == nullptr)
		return ;
	connectionState->reassembleBuffer.erase(connectionState->reassembleBuffer.begin(), connectionState->reassembleBuffer.begin() + messageEnd);
	std::string	cannedResponse = (
     "HTTP/1.1 404 Not Found\r\n"
     "Content-Length: 35\r\n"
     "Content-Type: text/plain\r\n"
	 "\r\n"
     "Hello This is Ratatouille server!\r\n"
	);
	connectionState->connection->sendData(std::vector<uint8_t>(cannedResponse.begin(), cannedResponse.end()));
}

void	testConnect(std::vector<uint8_t> data)
{
	if(tmpConnection == nullptr)
		return ;
	serv->dataReceived(tmpConnection, data);
}

void	Server::newConnection(Connection *newConnection){
	if (newConnection == nullptr)
		return ;
	ConnectionState *connectionState;

	connectionState->connection = newConnection;
	activeConnections.insert(connectionState);

	tmpConnection = connectionState;
	serv = this;
	newConnection->setDataReceivedDelegate(testConnect);
}
