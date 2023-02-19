/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:08:22 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 14:43:58 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINDINGSOCKET_H
# define BINDINGSOCKET_H
# include "SimpleSocket.hpp"

class BindingSocket : public SimpleSocket
{
private:
	BindingSocket(void);

public:
	BindingSocket(int domain, int service, int protocol, int port, u_long interface);
	~BindingSocket(void);
	int	connectToNetwork(int sock, struct sockaddr_in address);
};

#endif