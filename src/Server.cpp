/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 08:42:25 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#define BUFFSIZE 3000

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

// Server		*serv = NULL;
// ConnectionState	*tmpConnection = NULL;
// ConnectionState connectionState;

// void	test(Connection *connection)
// {
// 	// std::cout << "test called serv instance address " << serv << std::endl;
// 	serv->newConnection(connection);
// }

// bool	Server::mobilize(ServerTransport *newTransport, unsigned short newPort){

// 	transport = newTransport;
// 	serv = this;
// 	if(!transport->bindNetwork(newPort, test))
// 	{
// 		this->transport = NULL;
// 		return false;
// 	}
// 	return true;
// }

int	Server::startListen(std::string ipAddress, unsigned short port){
	struct sockaddr_in	serverAddr;
	int					sockfd;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("Error in Connection\n");
		return (-1);
	}
	printf("Server Socket is created\n");
	printf("sockfd : %i\n", sockfd);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = inet_addr(ipAddress.c_str());

	if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("Error in binding\n");
		return (-1);
	}
	printf("Bind to port %d\n", port);

	if ((listen(sockfd, 10)) == 0)
	{
		printf("Listening....\n");
	}
	else
	{
		printf("Error in Listening\n");
		return (-1);
	}
	return (sockfd);
}

int	Server::startListen(){
	// int					sockfd;

	this->sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sockfd < 0)
	{
		printf("Error in Connection\n");
		return (-1);
	}
	printf("Server Socket is created\n");
	printf("sockfd : %i\n", this->sockfd);
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(this->port);
	serverAddr.sin_addr.s_addr = inet_addr(this->host.c_str());
	printf("finished serv address config\n");
	if (bind(this->sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
	{
		printf("Error in binding\n");
		return (-1);
	}
	printf("Bind to port %d\n", port);

	if ((listen(this->sockfd, 10)) == 0)
	{
		printf("Listening....\n");
	}
	else
	{
		printf("Error in Listening\n");
		return (-1);
	}
	return (this->sockfd);
}

void	Server::demobilize(){
	
	// if (transport != NULL)
	// 	transport->releaseNetwork();
	// transport = NULL;
}

// void	Server::dataReceived(ConnectionState *connectionState, std::vector<unsigned char> data){
// 	Request		*request;
// 	std::size_t	messageEnd;

// 	connectionState->reassembleBuffer += std::string(data.begin(), data.end());
// 	// std::cout << connectionState->reassembleBuffer << std::endl;
// 	request = this->parseResquest(connectionState->reassembleBuffer, messageEnd);
// 	if (request == NULL)
// 		return ;
// 	connectionState->reassembleBuffer.erase(connectionState->reassembleBuffer.begin(), connectionState->reassembleBuffer.begin() + messageEnd);
// 	std::string	cannedResponse = (
//      "HTTP/1.1 404 Not Found\r\n"
//      "Content-Length: 35\r\n"
//      "Content-Type: text/plain\r\n"
// 	 "\r\n"
//      "Hello This is Ratatouille server!\r\n"
// 	);
// 	connectionState->connection->sendData(std::vector<unsigned char>(cannedResponse.begin(), cannedResponse.end()));
// }

// void	testConnect(std::vector<unsigned char> data)
// {
// 	if(tmpConnection == NULL)
// 		return ;
// 	serv->dataReceived(tmpConnection, data);
// }

// void	Server::newConnection(Connection *newConnection){
// 	if (newConnection == NULL)
// 		return ;

// 	connectionState.connection = newConnection;
// 	activeConnections.insert(&connectionState);

// 	tmpConnection = &connectionState;
// 	serv = this;
// 	newConnection->setDataReceivedDelegate(testConnect);
// }

void	Server::newConnection(int clientSocket, sockaddr_in & clientAddr){
	Request		*request;
	std::string	response;
	char		buffer[BUFFSIZE];
	Connection	connect(clientSocket);
	std::size_t	messageEnd;

	printf("Connection accepted from %s: %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	recv(clientSocket, buffer, 3000, 0);
	printf("%s\n", buffer);
	request = this->parseResquest(buffer, messageEnd);
	if (request == NULL)
		return ;
	response = connect.constructResponse(request, messageEnd);
	send(clientSocket, response.c_str(), strlen(response.c_str()), 0);
	bzero(buffer, sizeof(buffer));	
}

void	Server::newConnection(){
	Request		*request;
	std::string	response;
	char		buffer[BUFFSIZE];
	Connection	connect(clientfd);
	std::size_t	messageEnd;

	printf("Connection accepted from %s: %d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
	recv(clientfd, buffer, 3000, 0);
	printf("%s\n", buffer);
	request = this->parseResquest(buffer, messageEnd);
	if (request == NULL)
		return ;
	response = connect.constructResponse(request, messageEnd);
	send(clientfd, response.c_str(), strlen(response.c_str()), 0);
	bzero(buffer, sizeof(buffer));	
}

int	Server::acceptConnection(int sockfd, sockaddr_in & clientAddr){
    int					addrlen = sizeof(clientAddr);
	int					newSocket;
	
	newSocket = accept(sockfd, (struct sockaddr*)&clientAddr, (socklen_t *)&addrlen);
	if (newSocket < 0)
		return (-1);
	return (newSocket);
}

int	Server::acceptConnection(){
    int					addrlen = sizeof(clientAddr);
	
	clientfd = accept(sockfd, (struct sockaddr*)&clientAddr, (socklen_t *)&addrlen);
	if (clientfd < 0)
		return (-1);
	return (clientfd);
}