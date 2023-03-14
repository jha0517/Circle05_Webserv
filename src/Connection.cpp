/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:13:34 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 13:33:35 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Connection.hpp"


Connection::Connection() : dataReceivedDelegate(NULL)
{
}

Connection::Connection(int new_socketfd) : socketfd(new_socketfd)
{

}

Connection::~Connection()
{
}

std::string	Connection::constructResponse(Request *request, std::size_t messageEnd){
	std::string	responseStr;
	Response	response;

	std::cout << "method is " << request->method << std::endl;
	if (request->method == "GET")
		responseStr = response.getMethod(request, messageEnd);
	else if (request->method == "POST")
		responseStr = response.postMethod(request, messageEnd);
	else if (request->method == "DELETE")
		responseStr= response.deleteMethod(request, messageEnd);
	else
		return (NULL);
	return (responseStr);
}

// void Connection::setDataReceivedDelegate(DataReceivedDelegate newDataReceivedDelegate){
// 	dataReceivedDelegate = newDataReceivedDelegate;
// }
// void Connection::setBrokenDelegate(BrokenDelegate newBrokenDelegate){
// 	brokenDelegate = newBrokenDelegate;
// }
// void Connection::breakConnection(bool clean){
// 	(void) clean;
// }

// void Connection::sendData(std::vector<unsigned char> data){
// 	dataReceived.insert(dataReceived.end(), data.begin(), data.end());
// 	// for (std::vector<unsigned char>::iterator it = dataReceived.begin(); it != dataReceived.end(); ++it)
// 	// {
// 	// 	std::cout << *it;
// 	// }
// }

