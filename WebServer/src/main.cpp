/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:44:30 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/06 16:53:45 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Http/include/Server.hpp"
#include <csignal>
#include <iostream>

void	signalHandler(int signum)
{
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	signal(SIGINT, signalHandler);

	(void) av;
	(void) env;
	Server	server;
	bool	shutDown = false;

	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (EXIT_FAILURE);
	}
	while (!shutDown){
				
	}
	// manager.setConfiguration(av[1], env);

	
    return EXIT_SUCCESS;
}