/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:27 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/31 09:44:10 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_H
# define RESPONSE_H
# include "Uri.hpp"
# include "MessageHeaders.hpp"
# include "Server.hpp"
# include "Cgi.hpp"
# include "Request.hpp"
# include <map>
# include <ctime>
# include <fstream>
# include <iostream>

class Response
{
private:
	std::map<int, std::string>			statusCodeDic;
	std::map<std::string, std::string>	mimeMap;
	int									clientfd;
	std::string							getMimeType(std::string & filepath);
	std::string							getFormat(std::string & filepath);
public:
	Response();
	~Response();
	unsigned int	statusCode;
	std::string		reasonPhrase;
	Uri				target;
	MessageHeaders	headers;
	std::vector<char>	fileToBinary(std::string filename);
	std::string		status;
	// std::string		body;
	std::vector<char>	data;
	std::string		generateDateHeader();
	std::string		generateRawResponse(int code, MessageHeaders msg, std::string body);
	std::vector<char>	getMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode);
	std::vector<char>	postMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode);
	// std::string		deleteMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode);
	std::vector<char>	buildResponse(std::string dir, int errorCode);
	std::vector<char>	buildErrorResponse(std::string dir, int errorCode);
	std::vector<char>	buildResponseForCgi(std::vector<char> data, int code);
};

#endif
