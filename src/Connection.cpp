/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 08:42:17 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include <iostream>

# include <string>
# include <string.h>
# include <set>
# include <csignal>

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <netinet/in.h>
# include <arpa/inet.h>

Connection::Connection() : dataReceivedDelegate(NULL)
{
}

Connection::Connection(int new_socketfd) : socketfd(new_socketfd)
{

}

Connection::~Connection()
{
}

void Connection::setDataReceivedDelegate(DataReceivedDelegate newDataReceivedDelegate){
	dataReceivedDelegate = newDataReceivedDelegate;
}
void Connection::setBrokenDelegate(BrokenDelegate newBrokenDelegate){
	brokenDelegate = newBrokenDelegate;
}
void Connection::breakConnection(bool clean){
	(void) clean;
}

void Connection::sendData(std::vector<unsigned char> data){
	dataReceived.insert(dataReceived.end(), data.begin(), data.end());
	// for (std::vector<unsigned char>::iterator it = dataReceived.begin(); it != dataReceived.end(); ++it)
	// {
	// 	std::cout << *it;
	// }
}
