/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerTransport.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/06 11:25:53 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERTRANSPORT_H
# define SERVERTRANSPORT_H
# include <string>
# include "Connection.hpp"


typedef void(*NewConnectionDelegate)(Connection *);

class ServerTransport
{
public:


	ServerTransport();
	~ServerTransport();

	// virtual bool	setNewConnectionDelegate(NewConnectionDelegate newConnectionDelegate) = 0;
	// virtual	bool	bindNetwork(uint16_t port, NewConnectionDelegate newConnectionDelegate) = 0;	
	// virtual	void	releaseNetwork() = 0;
	virtual bool	setNewConnectionDelegate(NewConnectionDelegate newConnectionDelegate);
	virtual	bool	bindNetwork(uint16_t port, NewConnectionDelegate newConnectionDelegate);
	virtual	void	releaseNetwork();

	bool					bound;
	uint16_t				port;
	BrokenDelegate			brokenDelegate;
	DataReceivedDelegate	dataReceivedDelegate;
	NewConnectionDelegate	connectionDelegate;

private:
};

#endif
