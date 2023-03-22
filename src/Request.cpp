/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:35:23 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/22 16:33:29 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Request.hpp"

Request::Request()
{
}

Request::~Request()
{
}


bool	parseRequestLine(Request *request, const std::string requestLine)
{
	//parse the method
	std::size_t	methodDelimiter = requestLine.find(' ');
	if (methodDelimiter == std::string::npos)
		return (false);
	request->method = requestLine.substr(0, methodDelimiter);

	//parse the target URI
	std::size_t	targetDelimiter = requestLine.find(' ', methodDelimiter + 1);
	request->target.parsingFromString(requestLine.substr(methodDelimiter + 1, targetDelimiter - methodDelimiter - 1));
	// //parse the protocol
	request->protocol = requestLine.substr(targetDelimiter + 1);
	return (true);
}

bool	parseSize(const	std::string & numberString, size_t	& number)
{
	const	char *str = numberString.c_str();
	number = 0;
	for (unsigned char i= 0; i < numberString.length(); i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		// detect overflow
		size_t previousNumber = number;
		number *= 10;
		number += (unsigned short)(str[i] - '0');
		if (number / 10 != previousNumber)
			return false;
	}
	return true;
}
#include <cstdio>


std::size_t	vecFind(std::vector<char> rawRequest, std::string str)
{
	int	i = 0;
	int	v = 0;

	for (std::vector<char>::iterator it = rawRequest.begin(); it != rawRequest.end(); ++it)
	{
		i = 0;
		if (*it == str[i])
		{
			while (*(it + i) == str[i])
			{
				printf("Comparing vector char %c with str %c\n", *(it + 1), str[i]);
				if (i == str.length() - 1)
					return (v);
				i++;
			}
		}
		v++;
	}
	return (std::string::npos);
}

std::string	vecSubstr(std::vector<char> rawRequest, size_t start, size_t end)
{
	int	i = 0;
	int	v = 0;
	std::string	ret;

	for (std::vector<char>::iterator it = rawRequest.begin(); it != rawRequest.end(); ++it)
	{
		if (v == start)
		{
			i = 0;
			while (i != end - start)
			{
				ret += *(it + i);
				i++;
			}
		}
		v++;
	}
	return (ret);
}

bool	Request::parseResquest(const std::vector<char> rawRequest, size_t & messageEnd){
	std::string	CRLF = "\r\n";

	// parse the request line.
	// std::size_t	requestLineEnd	= rawRequest.find(CRLF);	
	std::size_t	requestLineEnd	= vecFind(rawRequest, CRLF);	
	if (requestLineEnd == std::string::npos)
		return (printf("No request Line End\n"), false);
	// std::string	requestLine = rawRequest.substr(0, requestLineEnd);
	std::string	requestLine = vecSubstr(rawRequest, 0, requestLineEnd);
	if (!parseRequestLine(this, requestLine))
		return (printf("request Line Not Parsable\n"), false);

	// parse the headers line.
	size_t	bodyOffset;
	size_t	headerOffset = requestLineEnd + CRLF.length();
	// if (!this->headers.parseFromString(rawRequest.substr(headerOffset), bodyOffset))
	if (!this->headers.parseFromString(vecSubstr(rawRequest, headerOffset, bodyOffset)))
		return (printf("Header Line End\n"), false);

	// check for content-length header. if present, use this to determine how many character should be in the body.
	bodyOffset += headerOffset;
	size_t	maxContentLength = rawRequest.size() - bodyOffset;
	size_t	contentLength;
	// extract body.
	if (this->headers.hasHeader("Content-Length"))
	{
		if (!parseSize(this->headers.getHeaderValue("Content-Length"), contentLength))
			return (printf("Content-length Size parsing\n"), false);
		if (contentLength > maxContentLength)
			return (printf("Content-length > MaxContentLength\n"), false);
		else
		{
			// this->body = rawRequest.substr(bodyOffset, contentLength);
			// std::cout << "Content Head ok, Body is : "<< body << std::endl;
			messageEnd = bodyOffset + contentLength + CRLF.length();
		}
	}
	else
	{
		// this->body = rawRequest.substr(bodyOffset);
		// std::cout << "Content Head non exist, Body is : "<< body << std::endl;
		messageEnd = bodyOffset;
	}
	return (true);
}
	
bool	Request::parseResquest(const std::vector<char> rawRequest){
	std::size_t	messageEnd;

	if (!this->parseResquest(rawRequest, messageEnd))
		return (false);
	return (true);
}

/*
bool	Request::parseResquest(const std::string &rawRequest, size_t & messageEnd){
	std::string	CRLF = "\r\n";

	// parse the request line.
	std::size_t	requestLineEnd	= rawRequest.find(CRLF);	
	if (requestLineEnd == std::string::npos)
		return (printf("No request Line End\n"), false);
	std::string	requestLine = rawRequest.substr(0, requestLineEnd);
	if (!parseRequestLine(this, requestLine))
		return (printf("request Line Not Parsable\n"), false);

	// parse the headers line.
	size_t	bodyOffset;
	size_t	headerOffset = requestLineEnd + CRLF.length();
	if (!this->headers.parseFromString(rawRequest.substr(headerOffset), bodyOffset))
		return (printf("Header Line End\n"), false);

	// check for content-length header. if present, use this to determine how many character should be in the body.
	bodyOffset += headerOffset;
	size_t	maxContentLength = rawRequest.length() - bodyOffset;
	size_t	contentLength;
	// extract body.
	if (this->headers.hasHeader("Content-Length"))
	{
		if (!parseSize(this->headers.getHeaderValue("Content-Length"), contentLength))
			return (printf("Content-length Size parsing\n"), false);
		if (contentLength > maxContentLength)
			return (printf("Content-length > MaxContentLength\n"), false);
		else
		{
			// this->body = rawRequest.substr(bodyOffset, contentLength);
			// std::cout << "Content Head ok, Body is : "<< body << std::endl;
			messageEnd = bodyOffset + contentLength + CRLF.length();
		}
	}
	else
	{
		// this->body = rawRequest.substr(bodyOffset);
		// std::cout << "Content Head non exist, Body is : "<< body << std::endl;
		messageEnd = bodyOffset;
	}
	return (true);
}
	
bool	Request::parseResquest(const std::string &rawRequest){
	std::size_t	messageEnd;

	if (!this->parseResquest(rawRequest, messageEnd))
		return (false);
	return (true);
}

*/