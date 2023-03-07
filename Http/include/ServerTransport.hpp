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

class ServerTransport
{
public:
	ServerTransport();
	~ServerTransport();
	virtual	bool	bindNetwork(uint16_t port, Connection *newConnectionDelegate);	
	virtual	void	releaseNetwork() = 0;
	bool			bound;
	uint16_t		port;

private:
};

#endif
