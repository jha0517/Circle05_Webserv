/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConnectingSocket.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:44:55 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 14:47:53 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTINGSOCKET_H
# define CONNECTINGSOCKET_H
# include "SimpleSocket.hpp"

class ConnectingSocket : public SimpleSocket
{
private:
	ConnectingSocket(void);
public:
	~ConnectingSocket(void);
	ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);
	int	connectToNetwork(int sock, struct sockaddr_in address);

};

#endif