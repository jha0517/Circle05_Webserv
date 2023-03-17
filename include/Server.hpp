/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/17 20:57:04 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include "Request.hpp"
# include <string>
# include <set>
# include <csignal>
# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <map>

class Server
{
public:
	struct LocationBlock{
		bool				isCgi_bin;		
		bool				hasReturn;
		std::map<std::string, std::string>	info;		
		// std::map<std::string, std::set<std::string>> data;
		// redirection "/redirection_intra/", "http://http://intra.42.fr/"
		// cgi         "root", "./"
		// 			   "cgi_path", set<std::string>"/usr/bin/python3", "/bin/bash"
		// 			   "cgi_ext", set<std::string>".py", ".sh"
		// dir			"/fruits"
	};

	Server();
	~Server();
	int						startListen();
	int						acceptConnection();
	void					newConnection();
	int						port;
	int						sockfd;
	bool					autoIndex;
	int						clientfd;
	int						maxClientBodySize;
	std::string				error_page;
	std::string				host;
	std::string				root;
	std::string				serverName;
	std::string				index;
	std::set<LocationBlock *>	locationBloc;
	std::set<std::string>	allowedMethod;
	void					*manager;
	std::string				findMatchingUri(std::string path);

private:
	Request					request;

	// std::set<Connection *>	activeConnections;
	struct sockaddr_in		serverAddr;
	struct sockaddr_in		clientAddr;
	std::map<std::string, std::string> mimeMap;

};

#endif
