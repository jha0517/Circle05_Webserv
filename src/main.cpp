/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/24 16:29:12 by hyunah           ###   ########.fr       */
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


std::string	checkFileAndGetContent(char *filename)
{
	std::string		src;
	std::string		rawRequest;
	std::ifstream	ifs;
	char	c;
	
	ifs.open(filename);
	if (ifs.fail())
		return ("");
	while (ifs.get(c))
		src+= c;
	ifs.close();
	return (src);
}

// int	main(int ac, const char **av, char **env)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) env;
// 	std::string pathphp = "/home/hyunah/Documents/webserv/data/upload.php";
// 	// char	*path[] = {strdup(pathphp.c_str()), NULL};
// 	// std::string pathphp = "hello";
// 	std::string arg1 = "php-cgi";
// 	char	*path[] = {strdup(arg1.c_str()), strdup(pathphp.c_str()), NULL};

// 	std::string newenv1 = "TESTHYUNAH=HYUNAH";
// 	char	*newEnv[] = {strdup(newenv1.c_str()), NULL};
	
// 	int id = fork();

// 	if (id == 0)
// 	{
// 		// printf("calling php function\n");
// 		// for (int i = 0; env[i] != NULL; i++)
// 		// {
// 		// 	printf("%i: %s\n", i, env[i]);
// 		// }
// 		execve("/usr/bin/php-cgi", path, newEnv);
// 		// execve("/usr/bin/echo", path, env);
// 		perror("execve");
// 		// execve("/usr/bin/php-cgi", (char * const)path.c_str(), env);
// 		// execl("/usr/bin/php -q", "/home/hyunah/Documents/webserv/data/test.php", NULL);
// 	}
// 	wait(NULL);
// 	// printf("End php function\n");
// }


int	main(int ac, char **av, char **env)
{
	// signal(SIGINT, signalHandler);

	(void)			env;
	std::vector<int> serverFds;
	ServerManager	serverManager;
	Config			config;

//config Start
	std::vector<Server *> servers;
	Server			server1;
	Server			server2;
	server1.port = 8000;
	server1.host = "127.0.0.1";
	server1.root = "./data";
	server1.serverName = "RatatouilleServer1";
	// server1.locationRoot = "/fruits"; //relative path ok
	server1.error_page = "/home/hyunah/Documents/webserv/data/error_pages";
	server1.maxClientBodySize = 400;
	server1.manager = &serverManager;
	server1.index = "index_1.html";
	server1.allowedMethod.insert("GET");
	server1.allowedMethod.insert("POST");
	Server::LocationBlock locbloc1;
	// Server::LocationBlock locbloc2;
	locbloc1.hasReturn = false;
	locbloc1.isCgi_bin = false;
	locbloc1.info.insert(std::pair<std::string, std::string>("dir", "/fruits"));
	locbloc1.info.insert(std::pair<std::string, std::string>("index", "yummyfruits.html"));
	server1.locationBloc.insert(&locbloc1);
	server1.maxClientBodySize = 30000;
	server1.env = env;
	servers.push_back(&server1);
	//=================================================

	server2.port = 8001;
	server2.host = "127.0.0.1";
	server2.root = "data"; // no 400
	server2.root = "/data"; // no
	// server2.root = "/home/hyunah/Documents/webserv/data"; path absolute //ok
	server2.serverName = "RatatouilleServer2";
	server2.error_page = "/home/hyunah/Documents/webserv/data/error_pages";
	// server2.locationRoot = "/fruits";
	server2.maxClientBodySize = 400;
	server2.manager = &serverManager;
	server2.allowedMethod.insert("GET");
	server2.allowedMethod.insert("POST");
	server2.allowedMethod.insert("DELETE");

	servers.push_back(&server2);
	config.servers = servers;

//config End

	if (ac > 2)
	{
		std::cerr << "Too many Arguments" << std::endl;
		return (EXIT_FAILURE);
	}
	if (ac == 2)
	{
		if (checkFileAndGetContent(av[1]).empty())
		{
			std::cerr << "Config file opening failed." << std::endl;
			return (EXIT_FAILURE);
		}
		if (!config.parseFromString(checkFileAndGetContent(av[1])))
		{
			std::cerr << "Config file parsing failed." << std::endl;
			return (EXIT_FAILURE);
		}
	}
	serverManager.initiate(config);
	serverManager.run();
	return (EXIT_SUCCESS);
}
