/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 14:59:17 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 15:09:52 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTENINGSOCKET_H
# define LISTENINGSOCKET_H
# include "BindingSocket.hpp"

class ListeningSocket : public BindingSocket
{
private:
	ListeningSocket(void);
	int	backlog;
	int	listening;
public:
	~ListeningSocket(void);
	ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bklg);
	int	startListening(int sock, int backlg);
	int	connectToNetwork(int sock, struct sockaddr_in address);
};

#endif