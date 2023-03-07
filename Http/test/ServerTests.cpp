/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerTests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:43:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/07 10:36:11 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../include/Server.hpp"

TEST(ServerTests, ParseGetRequest){
	Server	server;
	Request *request =  server.parseResquest(
     "GET /hello.txt HTTP/1.1\r\n"
     "User-Agent: curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3\r\n"
     "Host: www.example.com\r\n"
     "Accept-Language: en, mi\r\n"
	 "\r\n"
	);
	ASSERT_FALSE(request == nullptr);
	Uri	expectedUri;
	expectedUri.parsingFromString("/hello.txt");
	ASSERT_EQ("GET", request->method);
	ASSERT_EQ(expectedUri, request->target);
	ASSERT_TRUE(request->headers.hasHeader("User-Agent"));
	ASSERT_EQ("curl/7.16.3 libcurl/7.16.3 OpenSSL/0.9.7l zlib/1.2.3", request->headers.getHeaderValue("User-Agent"));
	ASSERT_TRUE(request->headers.hasHeader("Host"));
	ASSERT_EQ("www.example.com", request->headers.getHeaderValue("Host"));
	ASSERT_TRUE(request->headers.hasHeader("Accept-Language"));
	ASSERT_EQ("en, mi", request->headers.getHeaderValue("Accept-Language"));
	ASSERT_TRUE(request->headers.getBody().empty());
}

TEST(ServerTests, ParsePostRequest){
	Server	server;
	std::string	rawRequest = (
		"POST /test HTTP/1.1\r\n"
		"Host: foo.example\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Content-Length: 27\r\n"
		"\r\n"
		"field1=value1&field2=value2\r\n"
	);
	Request *request =  server.parseResquest(rawRequest);
	// Request *request =  server.parseResquest(rawRequest, messageEnd);
	ASSERT_FALSE(request == nullptr);
	Uri	expectedUri;
	expectedUri.parsingFromString("/test");
	ASSERT_EQ("POST", request->method);
	ASSERT_EQ(expectedUri, request->target);
	ASSERT_FALSE(request->headers.hasHeader("User-Agent"));
	ASSERT_EQ("application/x-www-form-urlencoded", request->headers.getHeaderValue("Content-Type"));
	ASSERT_TRUE(request->headers.hasHeader("Content-Length"));
	ASSERT_EQ("foo.example", request->headers.getHeaderValue("Host"));
	ASSERT_FALSE(request->headers.hasHeader("Accept-Language"));
	ASSERT_EQ("27", request->headers.getHeaderValue("Content-Length"));
	ASSERT_EQ("field1=value1&field2=value2", request->headers.getBody());
	ASSERT_EQ(27, request->headers.getBody().length());
}

TEST(ServerTests, ParseIncompleteBodyRequest){
	Server	server;
	std::string	rawRequest = (
		"POST /test HTTP/1.1\r\n"
		"Host: foo.example\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Content-Length: 100\r\n"
		"\r\n"
		"field1=value1&field2=value2\r\n"
	);
	Request *request =  server.parseResquest(rawRequest);
	ASSERT_TRUE(request == nullptr);
}

// TO DO:
// TEST(ServerTests, ParseIncompleteHeadersBetweenLinesRequest){
// 	Server	server;
// 	std::string	rawRequest = (
// 		"POST /test HTTP/1.1\r\n"
// 		"Host: foo.example\r\n"
// 		"Content-Type: application"
// 	);
// 	Request *request =  server.parseResquest(rawRequest);
// 	ASSERT_TRUE(request == nullptr);
// }


// TEST(ServerTests, ParseIncompleteRequestLine){
// 	Server	server;
// 	std::string	rawRequest = (
// 		"POST /test HTTP/1.1\r"
// 	);
// 	Request *request =  server.parseResquest(rawRequest);
// 	ASSERT_TRUE(request == nullptr);
// }


struct MockTransport : public ServerTransport
{
	uint16_t	port = 0;
	bool		bound = false;
	virtual bool	bindNetwork(uint16_t newPort, Connection *newConnectionDelegate)
	{
		port = newPort;
		bound = true;
		return true;
	}
	void	releaseNetwork(){
		bound = false;
	}
};

TEST(ServerTests, Mobilize)
{
	MockTransport	transport;
	Server			server;
	ASSERT_TRUE(server.mobilize(&transport, 1234));
	ASSERT_TRUE(transport.bound);
	ASSERT_EQ(1234, transport.port);
}

TEST(ServerTests, Demobilize)
{
	MockTransport	transport;
	Server			server;

	server.mobilize(&transport, 1234);
	server.demobilize();
	ASSERT_FALSE(transport.bound);
}


TEST(ServerTests, ReleaseNetWorkUponDestruction)
{
	MockTransport	transport;
	{
		Server			server;
		server.mobilize(&transport, 1234);
	}
	ASSERT_FALSE(transport.bound);
}
