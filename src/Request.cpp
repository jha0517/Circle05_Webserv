/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:35:23 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/16 17:08:29 by hyunah           ###   ########.fr       */
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

bool	Request::parseResquest(const std::string &rawRequest, size_t & messageEnd){
	std::string	CRLF = "\r\n";

	// parse the request line.
	std::size_t	requestLineEnd	= rawRequest.find(CRLF);	
	if (requestLineEnd == std::string::npos)
		return (false);
	std::string	requestLine = rawRequest.substr(0, requestLineEnd);
	if (!parseRequestLine(this, requestLine))
		return (false);

	// parse the headers line.
	size_t	bodyOffset;
	size_t	headerOffset = requestLineEnd + CRLF.length();
	if (!this->headers.parseFromString(rawRequest.substr(headerOffset), bodyOffset))
		return (false);

	// check for content-length header. if present, use this to determine how many character should be in the body.
	bodyOffset += headerOffset;
	size_t	maxContentLength = rawRequest.length() - bodyOffset;
	size_t	contentLength;
	// extract body.
	if (this->headers.hasHeader("Content-Length"))
	{
		if (!parseSize(this->headers.getHeaderValue("Content-Length"), contentLength))
			return (false);
		if (contentLength > maxContentLength)
			return (false);
		else
		{
			this->body = rawRequest.substr(bodyOffset, contentLength);
			messageEnd = bodyOffset + contentLength + CRLF.length();
		}
	}
	else
	{
		this->body = rawRequest.substr(bodyOffset);
		messageEnd = rawRequest.length();
	}
	return (true);
}
	
bool	Request::parseResquest(const std::string &rawRequest){
	std::size_t	messageEnd;

	if (!this->parseResquest(rawRequest, messageEnd))
		return (false);
	return (true);
}

