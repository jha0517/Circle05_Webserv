/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:52:05 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/04 10:20:22 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_H
# define SERVERMANAGER_H
# include <vector>
# include <sys/select.h>
# include "Server.hpp"
# include "Log.hpp"

class ServerManager
{
private:
	fd_set					currentSockets;
	fd_set					readySockets;
	bool					error;
	int						servBlockCount;
	int						max_socket_so_far;
	std::string				commonRoot;
	std::string				commonDefaultErrorPage;
	bool					commonAutoIndex;
	std::vector<int>		serverFds;

public:
	ServerManager();
	~ServerManager();
	ServerManager(ServerManager const & src);
	ServerManager &operator=(ServerManager const & rhs);
	
	Log		log;
	
	bool	initiate();
	bool	run();

	std::vector<Server *>	servers;
	void			setServerBlockCount(int servBlockCount);
	unsigned int	getServerBlockCount(void) const;
	void			setCommonParameter(std::string root, bool autoindex, std::string defaultErrorPage);
	void			setRoot(std::string root);
	void			setAutoIndex(bool autoindex);
	void			setDefaultErrorPage(std::string dir);

	int				closeAndFreeMem();
	void			addServerBlock();
};


#endif