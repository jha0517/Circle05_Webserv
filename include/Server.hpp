/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/02 18:22:23 by hyunah           ###   ########.fr       */
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
# include <cstddef>
class Server
{
public:
	Server();
	~Server();
	Server(Server const &src);
	Server &operator=(Server const &rhs);

	struct LocationBlock{
		std::string	dir;
		std::string	index;};

	struct CgiBlock{
		std::string	cgiPath;
		std::string	cgiScriptPath;
		std::set<std::string>	cgiExt;};

	struct RedirectBlock{
		std::string	dir;
		std::string	ret;
		};

	int					startListen();
	int					acceptConnection();
	void				newConnection();
	std::string			findMatchingUri(std::string path);

	void				setLocBlockCount(unsigned int i);
	void				setRedirectBlockCount(unsigned int i);

	void				setPort(unsigned short i);
	void				setUploadPath(std::string path);
	void				setHost(std::string str);
	void				setMaxClientBodySize(unsigned int i);
	void				setIndex(std::string index);
	void				setAllowedMethod(std::set<std::string> m);

	void				setCgiPath(std::string path);
	void				setCgiExt(std::set<std::string> extension);
	void				setCgiScriptPath(std::string path);

	unsigned int		getLocBlockCount();
	unsigned int		getRedirectBlockCount();
	void				addLocBlock(std::string dir, std::string index);
	void				addRedirectBlock(std::string dir, std::string ret);

	int						port;
	int						sockfd;
	bool					autoIndex;
	bool					hasCgiBlock;
	int						clientfd;
	int						maxClientBodySize;
	std::string				uploadPath;
	std::string				error_page;
	std::string				host;
	std::string				root;
	std::string				index;
	std::set<std::string>	allowedMethod;
	void					*manager;
	std::set<LocationBlock *>	locationBloc;
	std::set<RedirectBlock *>	redirectionBloc;
	CgiBlock				cgiBloc;
private:
	Request					request;
	struct sockaddr_in		serverAddr;
	struct sockaddr_in		clientAddr;
	unsigned int			nLoc;
	unsigned int			nRedirect;
};

#endif
