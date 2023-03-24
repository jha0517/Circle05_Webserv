/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 23:24:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/24 09:05:41 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/ServerManager.hpp"
#include "../include/Connection.hpp"

Server::Server() : sockfd(-1)
{
}

Server::~Server()
{
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

// std::vector<char>	fileToBinaryTest(std::string file_name1)
// {
// // string create_html_output_for_binary(const string &full_path)
// // {
//     std::vector<char> buffer;
//     const char* file_name = file_name1.c_str();

//     FILE* file_stream = fopen(file_name, "rb");

//     size_t file_size;
//     //... other code here

//     if(file_stream != NULL)
//     {
//         fseek(file_stream, 0, SEEK_END);
//         long file_length = ftell(file_stream);
//         rewind(file_stream);

//         buffer.resize(file_length);

//         file_size = fread(&buffer[0], 1, file_length, file_stream);
// 		printf("file size is %li\n", file_size);
//     }
// 	return (buffer);
//     // .... other code here
// }

// std::string intToString3(int a)
// {
// 	std::stringstream	ss;

//     ss << a;
//     return ss.str();
// }

void	Server::newConnection(){
	// std::string	response;
    std::vector<char> data;
	int			statusCode;
	Connection	connect(clientfd);
	ServerManager *servManag;

	servManag = (ServerManager *)manager;
	servManag->log.printConnection(inet_ntoa(clientAddr.sin_addr), clientfd);
	data = connect.constructResponse(*this, statusCode);

	// MessageHeaders	msg;

	// msg.addHeader("Content-Type", "application/msword");
	// msg.addHeader("Content-Transfer-Encoding", "binary");
	// data = fileToBinaryTest("/home/hyunah/Documents/webserv/data/fruits/sampleDOC.doc");
	// msg.addHeader("Content-Disposition", "inline; filename=\"myfile.doc\"");
	// msg.addHeader("Content-Length", intToString3(data.size()));
	// std::revstring msgTxt;
	// msgTxt = ("HTTP/1.1 200 OK\r\n");
	// msgTxt += msg.generateRawMsg();

	//big image? 81mb ok
	//png? ok
	//video? avi ok but it is downloading with rubbish filename.
	// pdf? yes.
	// 

	// data.insert(data.begin(), msgTxt.c_str(), msgTxt.c_str() + msgTxt.size());
	size_t	size = data.size();
	printf("data size is %li\n", size);
	int	numSent = 0;
	char	*p = static_cast<char *>(data.data());
	// while (size != i)
	while (size > 0)
	{
		// numSent = send(clientfd, p + i, 1, 0);
		numSent = send(clientfd, p, size, 0);
		// printf("Sending...\n");
		// printf("numSent: %i\n", numSent);
		if (numSent < 0)
		{
			std::cerr << "Sending message Failed" << std::endl;
			return ;
		}
		size -= numSent;
	}

	// if (send(clientfd, response.data(), strlen(response.c_str()), 0) < 0)
	// 	std::cerr << "Sending message Failed" << std::endl;
	servManag->log.printResponse(clientfd, statusCode);
	close(clientfd);
	// printf("Response:\n%s\n", response.c_str());
}

int	Server::acceptConnection(){
    int					addrlen = sizeof(clientAddr);
	
	clientfd = accept(sockfd, (struct sockaddr*)&clientAddr, (socklen_t *)&addrlen);
	if (clientfd < 0)
		return (-1);
	return (clientfd);
}

std::string	Server::findMatchingUri(std::string path){
	std::string ret;
	std::string indexfilename = "index.html";

	if (path.find(".") != std::string::npos)
	{
		return (this->root + path);
	}
	if (path == "/")
	{
		indexfilename = this->index;
		std::cout <<"final path is " << this->root + "/" + indexfilename << std::endl;
		return (this->root + "/" + indexfilename);
	}

	std::map<std::string, std::string>::iterator itMap;
	std::set<LocationBlock *>::iterator it;
	for (std::set<LocationBlock *>::iterator it = this->locationBloc.begin(); it != this->locationBloc.end(); ++it)
	{
		itMap = (*it)->info.find("dir");
		std::cout << "Looping throuh...: " << itMap->second << std::endl;
		if (itMap->second == path)
		{
			itMap = (*it)->info.find("index");
			if (itMap != (*it)->info.end())
				indexfilename = itMap->second;
			std::cout <<"final path is " << this->root + path  + "/" + indexfilename << std::endl;
			return (this->root + path  + "/" + indexfilename);
		}
	}
	return (ret);
}
