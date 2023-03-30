/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerManager.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:52:05 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/30 10:19:30 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERMANAGER_H
# define SERVERMANAGER_H
# include <vector>
# include <sys/select.h>
# include "Config.hpp"
# include "Server.hpp"
# include "Log.hpp"

class ServerManager
{
private:
	fd_set					currentSockets;
	fd_set					readySockets;
	std::vector<int>		serverFds;
	bool					error;
	int						servBlockCount;
	std::string				commonRoot;
	std::string				commonDefaultErrorPage;
	bool					commonAutoIndex;

public:
	ServerManager();
	ServerManager(ServerManager const & src);
	~ServerManager();
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

	Server			addServerBlock();

};

#endif