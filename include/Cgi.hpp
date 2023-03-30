/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:53:25 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/30 15:54:47 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP
# include "../include/Request.hpp"
# include "../include/Server.hpp"
# include <map>
# include <vector>

class Cgi
{

private:
	std::string							scriptPath;
	std::string							cmd;
	std::map<std::string, std::string>	cmdMap;
	std::vector<std::string>			env;

public:
	Cgi();
	Cgi(Cgi & src);
	Cgi &operator=(Cgi & rhs);
	~Cgi();
	bool			analyse(Server *server, Request *request);
	std::string 	getScriptPath();
	std::string		getCmd();
	void			addEnvParam(std::string key, std::string value);
	char			**getPathArray();
	char			**getEnvArray();
};

#endif