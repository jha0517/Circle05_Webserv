/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:35:23 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/22 17:00:18 by hyunah           ###   ########.fr       */
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
	size_t	i = 0;
	size_t	v = 0;

	for (std::vector<char>::iterator it = rawRequest.begin(); it != rawRequest.end(); ++it)
	{
		i = 0;
		if (*it == str[i])
		{
			while (*(it + i) == str[i])
			{
				printf("Comparing vector char %c with str %c\n", *(it + 1), str[i]);
				printf("i is %li, str.length is %li, returning %li\n", i, str.length()-1, v);
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
	size_t	i = 0;
	size_t	v = 0;
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
	std::size_t	requestLineEnd	= vecFind(rawRequest, CRLF);	
	if (requestLineEnd == std::string::npos)
		return (printf("No request Line End\n"), false);
	std::string	requestLine = vecSubstr(rawRequest, 0, requestLineEnd);
	if (!parseRequestLine(this, requestLine))
		return (printf("request Line Not Parsable\n"), false);

	// parse the headers line.
	size_t	bodyOffset = 0;
	size_t	headerOffset = requestLineEnd + CRLF.length();
	if (!this->headers.parseFromString(vecSubstr(rawRequest, headerOffset, rawRequest.size()), bodyOffset))
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
			messageEnd = bodyOffset + contentLength + CRLF.length();
	}
	else
		messageEnd = bodyOffset;
	return (true);
}
	
bool	Request::parseResquest(const std::vector<char> rawRequest){
	std::size_t	messageEnd;

	if (!this->parseResquest(rawRequest, messageEnd))
		return (false);
	return (true);
}
