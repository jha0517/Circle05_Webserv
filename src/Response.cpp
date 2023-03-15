/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 19:16:24 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Response.hpp"
#include <fstream>
Response::Response(/* args */)
{
	statusCodeDic.insert(std::pair<int, std::string>(200, "OK"));
	statusCodeDic.insert(std::pair<int, std::string>(404, "Not Found"));
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
	
	ifs.open(filename);
	if (!ifs)
	{
		std::cout << "File non-existance or Right Denied!" << std::endl;
		return ("");
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

std::string	Response::buildResponse(std::string dir, int code)
{
	MessageHeaders	msg;
	std::string		ret = "HTTP/1.1 ";
	std::string		body;
	std::string		filePath;

	ret += intToString(code) + " " + statusCodeDic[code] + "\r\n";

	filePath = dir;
	filePath += "/index.html";
	std::cout << "FilePathName : " << filePath << std::endl;
	body = check_filename_get_str(filePath.c_str());
	if (body.empty())
		return (ret);
	msg.addHeader("Content-Type", "text/html");
	msg.addHeader("Content-Length", intToString(body.length()));
	ret += msg.generateRawMsg();
	ret += body;
	return (ret);
}


std::string	Response::buildErrorResponse(std::string dir, int code)
{
	MessageHeaders	msg;
	std::string		ret = "HTTP/1.1 ";
	std::string		body;
	std::string		filePath;

	ret += intToString(code) + " " + statusCodeDic[code] + "\r\n";

	filePath = dir;
	filePath += intToString(code) + ".html";
	// std::cout << "FilePathName : " << filePath << std::endl;
	body = check_filename_get_str(filePath.c_str());
	if (body.empty())
		return (ret);
	msg.addHeader("Content-Type", "text/html");
	msg.addHeader("Content-Length", intToString(body.length()));
	ret += msg.generateRawMsg();
	ret += body;
	return (ret);
}

std::string	Response::getMethod(Server &server, Request *request, std::size_t messageEnd){
	(void) messageEnd;
	std::string	ret;
	if (request->target.hasPath())
	{
		if (request->target.generateString() == "/" || request->target.generateString() == "/index.html")
		{
			ret = buildResponse(server.root, 200);
			return ret;
		}
		// findfile(request->target.generateString);
	}
	else
	{
		// if (server.root.empty())
		ret = buildErrorResponse(server.error_page, 500);
		return (ret);
		// else
			// return index.html
	}
	// ret = (
    //  "HTTP/1.1 404 Not Found\r\n"
    //  "Content-Length: 35\r\n"
    //  "Content-Type: text/plain\r\n"
	//  "\r\n"
    //  "Hello This is Ratatouille server!\r\n"
	// );
	return (ret);
}

std::string	Response::postMethod(Server &server, Request *request, std::size_t messageEnd){
	(void) request;
	(void) messageEnd;
	(void) request;
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

std::string	Response::deleteMethod(Server &server, Request *request, std::size_t messageEnd){
	(void) request;
	(void) messageEnd;
	(void) request;
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