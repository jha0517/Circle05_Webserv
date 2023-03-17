/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Log.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:36:10 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/17 16:21:27 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOG_H
# define LOG_H
# include <ctime>
# include <iostream>
# include <ostream>
# include "Colors.hpp"
# include "Server.hpp"
# define FAILED RED

class Log
{
private:
public:
	Log();
	~Log();
	void	printInit();
	void	printServerCreation(bool success, Server *server);
	void	printConnection(std::string clientHost, unsigned int clientFd);
	void	printRequest(unsigned int clientFd, std::string method, std::string uri);
	void	printResponse(unsigned int clientFd, int statusCode);
};

#endif