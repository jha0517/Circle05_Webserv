/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:27 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/16 08:40:17 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_H
# define RESPONSE_H
# include "Uri.hpp"
# include "MessageHeaders.hpp"
# include "Server.hpp"
# include "Webserv.hpp"
# include <map>
# include <fstream>


class Response
{
private:
	std::map<int, std::string>	statusCodeDic;
public:
	Response();
	~Response();
	unsigned int	statusCode;
	std::string		reasonPhrase;
	Uri				target;
	MessageHeaders	headers;
	std::string		status;
	std::string		body;
	std::string		generateRawResponse(int code, MessageHeaders msg, std::string body);
	std::string		getMethod(Server &server, Request *request, std::size_t messageEnd);
	std::string		postMethod(Server &server, Request *request, std::size_t messageEnd);
	std::string		deleteMethod(Server &server, Request *request, std::size_t messageEnd);
	std::string		buildResponse(std::string dir, int errorCode);
	std::string		buildErrorResponse(std::string dir, int errorCode);
};

#endif
