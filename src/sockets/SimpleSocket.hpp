/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleSocket.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:16:47 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 15:06:59 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLESOCKET_H
# define SIMPLESOCKET_H
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <iostream>
# include <stdlib.h>

class SimpleSocket
{
private:
	SimpleSocket(void);
	struct	sockaddr_in	address;
	int					sock;

protected:
	int					connection;

public:
	SimpleSocket(int domain,int service, int protocol, int port, u_long interface);
	~SimpleSocket(void);
	struct sockaddr_in	getAddress(void) const;
	int					getSocket(void) const;
	int					getConnection(void) const;
	void				testConnection(int itemToTest) const;
	virtual int 		connectToNetwork(int sock, struct sockaddr_in * address) = 0;
};



#endif
