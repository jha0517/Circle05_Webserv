/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:52:05 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 11:43:04 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_H
# define SERVERMANAGER_H
# include <vector>
# include <sys/select.h>
# include "Config.hpp"
# include "Server.hpp"

class ServerManager
{
private:
	fd_set					currentSockets;
	fd_set					readySockets;
	std::vector<Server *>	servers;
	std::vector<int>		serverFds;
	bool					error;

public:
	ServerManager();
	~ServerManager();
	bool initiate(Config & config);
	bool run();
};

#endif