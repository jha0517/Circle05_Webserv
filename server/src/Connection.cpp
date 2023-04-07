/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyujung <hyujung@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/07 15:20:51 by hyujung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include "../include/ServerManager.hpp"
#include "../include/Response.hpp"

Connection::Connection(): cgiState(0){}

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

bool	checkURIexist(std::string path)
{
	struct stat sb;

	std::cout << "Checking if path exist : " << path << std::endl;
    if (stat(path.c_str(), &sb) == 0)
		return (true);
	return (false);
}

std::vector<char>	Connection::constructResponse(){
	std::string		responseStr;
	std::size_t		messageEnd;
	Response		response;
	
	// Not allowed Method
	if (this->serv->allowedMethod.find(this->request.method) == this->serv->allowedMethod.end())
	{
		std::cout << "Not allowed Method.\n";
		return (response.buildErrorResponse(this->serv->error_page, 405));
	}
	// Not supported Protocol
	if (this->request.protocol != "HTTP/1.1")
	{
		std::cout << "Protocol not supported.\n";
		return (response.buildErrorResponse(this->serv->error_page, 505));
	}
	// build response
	messageEnd = 0;
	if (this->request.method == "GET")
		dataResponse = response.getMethod(*(this->serv), &this->request, messageEnd);
	else if (this->request.method == "POST")
	{
		dataResponse = response.postMethod(*(this->serv), &this->request, messageEnd);
	}
	// else if (request.method == "DELETE")
		// responseStr= response.deleteMethod(server, &request, messageEnd, statusCode);
	else
		return (response.buildErrorResponse(this->serv->error_page, 500));
	return (dataResponse);
}

void	Connection::readRequest(const int &i, ServerManager *servManag){
	char				buffer[BUFFSIZE];
	std::size_t			messageEnd;
	// int					statusCode;
	Response			response;
	int					byte;

	servManag->log.printConnection(inet_ntoa(clientAddr.sin_addr), i);
	// std::cout << "new connection data size has to be 0: " << data.size() << std::endl;
	byte = recv(i, buffer, BUFFSIZE, 0);
	if (byte < 0)
	{
		servManag->log.printError("Recv Failed.");
		servManag->closeConnection(i);
		return ;
	}
	if (byte == 0)
	{
		servManag->closeConnection(i);
		return ;
	}
	if (byte != 0)
	{
		dataReceived.insert(dataReceived.end(), buffer, buffer + byte);
		bzero(buffer, sizeof(buffer));
	}
	std::cout << "dataReceived.size()"<< dataReceived.size() << "this->serv->maxClientBodySize" << this->serv->maxClientBodySize << std::endl;
	if (dataReceived.size() > (unsigned long)this->serv->maxClientBodySize)
	{
		dataResponse = response.buildErrorResponse(this->serv->error_page, 413);
		servManag->removeFromSet(i, servManag->readSockets);
		std::cout << "Adding "<< i << "to WriteSockets" << std::endl;
		servManag->addToSet(i, servManag->writeSockets);
		return ;
	}
	if (this->request.parseResquest(dataReceived, messageEnd))
	{
		servManag->log.printRequest(i, this->request.method, this->request.target.generateString());
		// printf("Parsing SUCCESS: %li\n", this->dataReceived.size());
		// std::cout << request;
		dataReceived.clear();
		dataResponse = constructResponse();
		// printData(dataResponse);
		servManag->removeFromSet(i, servManag->readSockets);
		std::cout << "Adding "<< i << "to WriteSockets" << std::endl;
		servManag->addToSet(i, servManag->writeSockets);
	}
	// printf("Parsing FAILED: %li\n", this->dataReceived.size());
	return ;
}

void	Connection::writeResponse(const int &i, ServerManager *servManag)
{
	size_t	size = this->dataResponse.size();
	int		numSent = 0;
	char	*p = static_cast<char *>(this->dataResponse.data());

	std::cout << "received data size for writing side: " << this->dataResponse.size() << std::endl;
	while (size > 0)
	{
		numSent = send(i, p, size, 0);
		if (numSent < 0)
			return (servManag->log.printError("Sending message Failed"));
		size -= numSent;
	}
	// printData(dataResponse);
	servManag->log.printResponse(i, 202);
	if (dataResponse.size() != 0)
		dataResponse.clear();
	// close(clientfd);
}

void	Connection::cgiRequest(const int &i, ServerManager *servManag)
{
	Cgi cgi;
	int	errorCode;
	(void) i;
	(void) servManag;
	errorCode = cgi.analyse(this->serv, &this->request);
	if (errorCode != 0)
	{
		Response response;
		dataResponse = response.buildErrorResponse(this->serv->error_page, errorCode);
		this->cgiState = 0;
	}
	cgi.addEnvParam(request.target.getQuery());
	this->dataResponse = cgi.execute();
	this->cgiState = 2;
}

void	Connection::cgiResponse(const int &i, ServerManager *servManag)
{
	Response response;

	(void) i;
	(void) servManag;
	this->dataResponse = response.buildResponseForCgi(this->dataResponse, 200);
	this->cgiState = 0;
}

