/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/30 10:18:09 by hyunah           ###   ########.fr       */
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
	ServerManager	servManager;
	
	//config Start
	servManager.setRoot("./data");
	servManager.setAutoIndex(true);
	servManager.setDefaultErrorPage("/error_pages/404.html");

	servManager.setServerBlockCount(1);
	// iterate number of server block
	for (unsigned int num = 0; num < servManager.getServerBlockCount(); num++)
	{
		Server	sv;
		
		// add server and set param
		sv = servManager.addServerBlock();
		sv.setPort(8000);
		sv.setHost("127.0.0.1");
		sv.setMaxClientBodySize(1024);
		sv.setIndex("index_1.html");

		std::set<std::string> method;
		method.insert("GET");
		method.insert("POST");
		sv.setAllowedMethod(method);

		sv.hasCgiBlock = 1;
		// if there is add cgiBlock and set param
		if (sv.hasCgiBlock)
		{
			sv.setCgiPath("./data/cgi-bin");
			std::set<std::string> ex;
			ex.insert(".php");
			sv.setCgiExt(ex);
		}
	
		sv.setLocBlockCount(1);
		// if there is add cgiBlock and set param
		for (unsigned int num = 0; num < sv.getLocBlockCount(); num++)
			sv.addLocBlock("/fruits", "yummyfruits.html");

		sv.setRedirectBlockCount(1);
		for (unsigned int num = 0; num < sv.getRedirectBlockCount(); num++)
			sv.addRedirectBlock("/redirection_intra/", "http://http://intra.42.fr/");
	}

//config End

	servManager.initiate();
	servManager.run();
	return (EXIT_SUCCESS);
}
