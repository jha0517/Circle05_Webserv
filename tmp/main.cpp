/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:25:27 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/06 16:43:02 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// # include <csignal>
// # include <iostream>
// # include "http/include/ServerManager.hpp"

// void	signalHandler(int signum)
// {
// 	std::cout << "\nLeaving the server...Bye!" << std::endl;
// 	exit(signum);
// }

int	main(int ac, char **av, char **env)
{
    // ServerManager manager;
	// signal(SIGINT, signalHandler);

	// (void) av;
	// (void) env;
	// if (ac != 2)
	// {
	// 	std::cerr << "Need 1 config file OR default path." << std::endl;
	// 	return (1);
	// }
	// try{
	// 	// manager.setConfiguration(av[1], env);
	// }
	// catch(std::exception& e){
	// 	std::cerr << e.what() << std::endl;
	// 	return (2);
	// }
	// // manager.runServer(manager.config.getPort());
	// manager.runServer(8080);
    return 0;
}