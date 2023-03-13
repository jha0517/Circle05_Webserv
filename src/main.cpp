/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/13 21:13:50 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include <csignal>
#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8000

void	signalHandler(int signum)
{
	(void) signum;
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signalHandler);

	(void)				av;
	(void)				env;
	Server				server;

	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (EXIT_FAILURE);
	}
	if (server.startListen("127.0.0.1", PORT) < 0)
		return (EXIT_FAILURE);
	while (1)
	{
		if (server.acceptConnection() < 0)
		{
			std::cout << "Error in Accept\n" << std::endl;
			return (EXIT_FAILURE);
		}
	}
   return EXIT_SUCCESS;
}