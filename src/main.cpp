
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/04 18:11:49 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/ServerManager.hpp"
#include <csignal>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	ServerManager	sm;
	

	//config Start
	sm.setRoot("./data");
	sm.setAutoIndex(true);
	sm.setDefaultErrorPage(".data/error_pages/404.html");

	sm.setServerBlockCount(1);
	// iterate number of server block
	for (unsigned int i = 0; i < sm.getServerBlockCount(); i++)
	{
		// add server and set param
		sm.addServerBlock();
		sm.servers[i]->setPort(8003);
		sm.servers[i]->setHost("127.0.0.1");
		sm.servers[i]->setMaxClientBodySize(1024);
		sm.servers[i]->setIndex("index_1.html");
		sm.servers[i]->setUploadPath("./data/upload");

		std::set<std::string> method;
		method.insert("GET");
		method.insert("POST");
		sm.servers[i]->setAllowedMethod(method);

		sm.servers[i]->hasCgiBlock = 1;
		// if there is add cgiBlock and set param
		if (sm.servers.at(i)->hasCgiBlock)
		{
			sm.servers.at(i)->setCgiPath("/usr/bin/cgi-bin");
			sm.servers.at(i)->setCgiScriptPath("./data/cgi-bin");
			std::set<std::string> ex;
			ex.insert(".php");
			sm.servers.at(i)->setCgiExt(ex);
		}

		sm.servers.at(i)->setLocBlockCount(1);
		// if there is add cgiBlock and set param
		for (unsigned int j = 0; j < sm.servers.at(i)->getLocBlockCount(); j++)
			sm.servers.at(i)->addLocBlock("/fruits", "yummyfruits.html");

		sm.servers.at(i)->setRedirectBlockCount(1);
		for (unsigned int k = 0; k < sm.servers.at(i)->getRedirectBlockCount(); k++)
			sm.servers.at(i)->addRedirectBlock("/redirection_intra/", "https://www.google.com/");
	}

//config End

	if (!sm.initiate())
		return (EXIT_FAILURE);
	if (sm.run())
	{
		sm.closeAndFreeMem();
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
