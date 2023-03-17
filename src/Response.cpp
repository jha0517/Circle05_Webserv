/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/17 20:46:12 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Response.hpp"

Response::Response()
{
	statusCodeDic.insert(std::pair<int, std::string>(200, "OK"));
	statusCodeDic.insert(std::pair<int, std::string>(404, "Not Found"));
	statusCodeDic.insert(std::pair<int, std::string>(400, "Bad Request"));
}

Response::~Response()
{
}

std::string	check_filename_get_str(const char *filename)
{
	std::string		src;
	std::string		buffer;
	std::ifstream	ifs;
	char	c;
	
	// if (checkPathRelative())
	ifs.open(filename);
	if (!ifs)
	{
		std::cout << "File non-existance or Right Denied!" << std::endl;
		return ("404");
	}
	while (ifs.get(c))
		src+= c;
	ifs.close();
	if (src.empty())
	{
		std::cout << "File is empty!" << std::endl;
		return ("");
	}
	return (src);
}

std::string intToString(int a)
{
	std::stringstream	ss;

    ss << a;
    return ss.str();
}

std::string	Response::generateRawResponse(int code, MessageHeaders msg, std::string body){
	if (statusCodeDic[code].empty())
		std::cout << "There is no status available in Dictionnary for code " << intToString(code) << std::endl;
	std::string ret = ("HTTP/1.1 " + intToString(code) + " " + statusCodeDic[code] + "\r\n");
	if (!msg.hasHeader("Content-Length"))
		msg.addHeader("Content-Length", intToString(body.length()));
	else
	{
		if (msg.getHeaderValue("Content-Length") != intToString(body.length()))
			msg.setHeaderValue("Content-Length", intToString(body.length()));
	}
	ret += msg.generateRawMsg();
	ret += body;
	return (ret);
}

std::string	getMimeType(std::string filepath)
{
	std::size_t	formatDelimitor;
	std::string	format;
	formatDelimitor = filepath.find_last_of(".");
	format = filepath.substr(formatDelimitor);
	std::cout << "format is : " << format << std::endl;
	return ("");
}
std::string	Response::buildResponse(std::string dir, int code)
{
	MessageHeaders	msg;
	std::string		ret;

	body = check_filename_get_str(dir.c_str());
	if (body.empty())
		return ("");
	getMimeType(dir);
	msg.addHeader("Content-Type", "text/html");
	msg.addHeader("Content-Length", intToString(body.length()));
	return (generateRawResponse(code, msg, body));
}

std::string	Response::buildErrorResponse(std::string dir, int code)
{
	MessageHeaders	msg;
	std::string		ret;
	std::string		body;
	std::string		filePath;

	filePath = dir + "/"+ intToString(code) + ".html";
	std::cout << "FilePathName : " << filePath << std::endl;
	body = check_filename_get_str(filePath.c_str());
	if (body.empty())
		return ("");
	ret += "HTTP/1.1 " + intToString(code) + " " + statusCodeDic[code] + "\r\n";
	msg.addHeader("Content-Type", "text/html");
	msg.addHeader("Content-Length", intToString(body.length()));
	ret += msg.generateRawMsg();
	ret += body;
	return (ret);
}

std::string	Response::getMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
	(void) messageEnd;
	std::string	ret;

	// GET must have empty body, if not, Bad Request.
	if (!request->body.empty())
	{
		statusCode = 400;
		return (buildErrorResponse(server.error_page, 400));
	}
	ret = buildResponse(server.findMatchingUri(request->target.generateString()), 200);
	statusCode = 200;
	if (ret.empty())
	{
		statusCode = 400;
		return (buildErrorResponse(server.error_page, 400));	
	}
	return (ret);
}

std::string	Response::postMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
	(void) request;
	(void) messageEnd;
	(void) request;
	(void) statusCode;
	(void) server;
	std::cout << "In PostMethod\n";
	std::string	expectedResponse = (
     "HTTP/1.1 404 Not Found\r\n"
     "Content-Length: 35\r\n"
     "Content-Type: text/plain\r\n"
	 "\r\n"
     "Hello This is Ratatouille server!\r\n"
	);
	return (expectedResponse);
}

std::string	Response::deleteMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
	(void) request;
	(void) messageEnd;
	(void) request;
	(void) statusCode;
	(void) server;
	std::cout << "In DeleteMethod\n";
	std::string	expectedResponse = (
     "HTTP/1.1 404 Not Found\r\n"
     "Content-Length: 35\r\n"
     "Content-Type: text/plain\r\n"
	 "\r\n"
     "Hello This is Ratatouille server!\r\n"
	);
	return (expectedResponse);
}