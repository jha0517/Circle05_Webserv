/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/08 14:33:00 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"
#include <iostream>

Connection::Connection() : dataReceivedDelegate(nullptr)
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
void Connection::breakConnection(bool clean){}
void Connection::sendData(std::vector<uint8_t> data){
	dataReceived.insert(dataReceived.end(), data.begin(), data.end());
	std::cout << "HELLO SEND DATA\n";
	for (std::vector<uint8_t>::iterator it = dataReceived.begin(); it != dataReceived.end(); ++it)
	{
		std::cout << *it;
	}
} // uint_8 0-255, == uchar
