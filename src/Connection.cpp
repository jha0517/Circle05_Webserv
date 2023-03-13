/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/13 18:39:42 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include <iostream>

Connection::Connection() : dataReceivedDelegate(NULL)
{
}

Connection::Connection(char *ipAddress, int port){
	(void) ipAddress;
	(void) port;
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
	// std::cout << "HELLO SEND DATA\n";
	// for (std::vector<unsigned char>::iterator it = dataReceived.begin(); it != dataReceived.end(); ++it)
	// {
	// 	std::cout << *it;
	// }
	// std::cout << "END OF DATA\n";
}
