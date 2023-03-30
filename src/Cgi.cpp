/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 15:54:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/30 15:54:37 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cgi.hpp"

Cgi::Cgi(){
    this->cmdMap.insert(std::make_pair(".php", "php-cgi"));
    this->cmdMap.insert(std::make_pair(".py", "python"));
}

Cgi::~Cgi(){}

Cgi::Cgi(Cgi & src){
	*this = src;
}
Cgi & Cgi::operator=(Cgi & rhs){
	if (this != &rhs)
	{
		this->cmd = rhs.cmd;
		this->scriptPath = rhs.scriptPath;
	}
	return (*this);
}

std::string Cgi::getScriptPath(){return (this->scriptPath);}
std::string	Cgi::getCmd(){return (this->cmd);}

void	Cgi::addEnvParam(std::string key, std::string value){this->env.push_back(key + "=" + value);}

bool	Cgi::analyse(Server *server, Request *request){
	//scriptPath
	this->scriptPath = server->cgiBloc.cgiPath + "/" + request->target.getPath().back();
	
	//cmd
	for (std::map<std::string, std::string>::iterator it = this->cmdMap.begin();\
		it != this->cmdMap.end(); ++it)
	{
		if (request->target.getPath().back().find(it->first))
			this->cmd = it->second;
	}

	//env
	addEnvParam("AUTH_TYPE", "Basic");
	// addEnvParam(env, "CONTENT_LENGTH", request->headers.getHeaderValue("Content-Length"));
	addEnvParam("CONTENT_TYPE", request->headers.getHeaderValue("Content-Type"));
	addEnvParam("GATEWAY_INTERFACE", "CGI/1.1");
	addEnvParam("SCRIPT_NAME", "upload.php");
	addEnvParam("SCRIPT_FILENAME", this->scriptPath);
	addEnvParam("REDIRECT_STATUS", "200");
	addEnvParam("QUERY_STRING", request->target.getQuery());
	addEnvParam("REMOTE_ADDR", server->host + ":" + intToString(server->port));
	addEnvParam("SERVER_NAME", server->host);
	addEnvParam("SERVER_PORT", intToString(server->port));
	addEnvParam("REQUEST_METHOD", request->method);
	addEnvParam("REQUEST_URI", request->target.generateString());
	addEnvParam("SERVER_PROTOCOL", "HTTP/1.1");
	return (true);
}

char	**Cgi::getPathArray(){
	char	**path = (char **)calloc(sizeof(char *), 2 + 1);
	path[0] = strdup(this->cmd.c_str());
	path[1] = strdup(this->scriptPath.c_str());
	path[2] = NULL;

	return (path);	
}

char	**Cgi::getEnvArray(){
	char	**newEnv = (char **)calloc(sizeof(char *), env.size() + 1);
	int i = 0;

	for (std::vector<std::string>::iterator it = env.begin(); it != env.end(); ++it)
	{
		newEnv[i] = strdup(it->c_str());
		std::cout << i << ". " << it->c_str() << std::endl;
		i++;
	}
	return (newEnv);
}
