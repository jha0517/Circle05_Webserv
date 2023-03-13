/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerTests.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:43:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/13 17:26:52 by hyunah           ###   ########.fr       */
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
	ASSERT_FALSE(request == NULL);
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
}

TEST(ServerTests, ParsePostRequest){
	Server	server;
	size_t	messageEnd;
	std::string	rawRequest = (
		"POST /test HTTP/1.1\r\n"
		"Host: foo.example\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n"
		"Content-Length: 27\r\n"
		"\r\n"
		"field1=value1&field2=value2\r\n"
	);
	Request *request =  server.parseResquest(rawRequest, messageEnd);
	// Request *request =  server.parseResquest(rawRequest, messageEnd);
	ASSERT_FALSE(request == NULL);
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
	ASSERT_EQ("field1=value1&field2=value2", request->body);
	ASSERT_EQ(27, request->body.length());
}

TEST(ServerTests, MessageEnd){
	Server	server;
	size_t	messageEnd;
	std::string	rawRequest = (
		"POST /test HTTP/1.1\r\n"
		"Content-Length: 1\r\n"
		"\r\n"
		"1\r\n"
	);
	Request *request =  server.parseResquest(rawRequest, messageEnd);
	ASSERT_EQ(rawRequest.length(), messageEnd);
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
	ASSERT_TRUE(request == NULL);
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
// 	ASSERT_TRUE(request == NULL);
// }


// TEST(ServerTests, ParseIncompleteRequestLine){
// 	Server	server;
// 	std::string	rawRequest = (
// 		"POST /test HTTP/1.1\r"
// 	);
// 	Request *request =  server.parseResquest(rawRequest);
// 	ASSERT_TRUE(request == NULL);
// }

TEST(ServerTests, Mobilize)
{
	// ServerTransport	transport;
	// Server			server;
	
	// ASSERT_TRUE(server.mobilize(&transport, 1234));
	// ASSERT_TRUE(transport.bound);
	// ASSERT_EQ(1234, transport.port);
	// ASSERT_FALSE(transport.connectionDelegate == NULL);
}

TEST(ServerTests, Demobilize)
{
	// ServerTransport	transport;
	// Server			server;

	// server.mobilize(&transport, 1234);
	// server.demobilize();
	// ASSERT_FALSE(transport.bound);
}

TEST(ServerTests, ReleaseNetWorkUponDestruction)
{
	// ServerTransport	transport;
	// // MockTransport	transport;
	// {
	// 	Server			server;
	// 	server.mobilize(&transport, 1234);
	// }
	// ASSERT_FALSE(transport.bound);
}

TEST(ServerTests, Expect404FromClientRequestInOnePiece)
{
	// ServerTransport	transport;
	// Connection		connection;
	// Server			server;
	
	// server.mobilize(&transport, 1234);
	// transport.connectionDelegate(&connection);
	// ASSERT_FALSE(connection.dataReceivedDelegate == NULL);
	// std::string	rawRequest = (
	// 	"POST /test HTTP/1.1\r\n"
	// 	"Host: foo.example\r\n"
	// 	"Content-Type: application/x-www-form-urlencoded\r\n"
	// 	"Content-Length: 27\r\n"
	// 	"\r\n"
	// 	"field1=value1&field2=value2\r\n"
	// );
	// ASSERT_TRUE(connection.dataReceived.empty());
	// connection.dataReceivedDelegate(std::vector<unsigned char>(rawRequest.begin(), rawRequest.end()));
	// std::string	expectedResponse = (
    //  "HTTP/1.1 404 Not Found\r\n"
    //  "Content-Length: 35\r\n"
    //  "Content-Type: text/plain\r\n"
	//  "\r\n"
    //  "Hello This is Ratatouille server!\r\n"
	// );
	// ASSERT_FALSE(connection.dataReceived.empty());
	// ASSERT_EQ(expectedResponse, std::string(connection.dataReceived.begin(), connection.dataReceived.end()));
}

// TEST(ServerTests, Expect404FromClientRequestInTwoPieces)
// {
// 	ServerTransport	transport;
// 	Connection		connection;
// 	Server			server;
	
// 	server.mobilize(&transport, 1234);
// 	transport.connectionDelegate(&connection);
// 	ASSERT_FALSE(connection.dataReceivedDelegate == NULL);
// 	std::string	rawRequest = (
// 		"POST /test HTTP/1.1\r\n"
// 		"Host: foo.example\r\n"
// 		"Content-Type: application/x-www-form-urlencoded\r\n"
// 		"Content-Length: 27\r\n"
// 		"\r\n"
// 		"field1=value1&field2=value2\r\n"
// 	);
// 	ASSERT_TRUE(connection.dataReceived.empty());
// 	connection.dataReceivedDelegate(std::vector<unsigned char>(rawRequest.begin(), rawRequest.begin() + rawRequest.length() / 2));
// 	ASSERT_TRUE(connection.dataReceived.empty());
// 	connection.dataReceivedDelegate(std::vector<unsigned char>(rawRequest.begin() + rawRequest.length() / 2, rawRequest.end()));
// 	std::string	expectedResponse = (
//      "HTTP/1.1 404 Not Found\r\n"
//      "Content-Length: 35\r\n"
//      "Content-Type: text/plain\r\n"
// 	 "\r\n"
//      "Hello This is Ratatouille server!\r\n"
// 	);
// 	ASSERT_FALSE(connection.dataReceived.empty());
// 	ASSERT_EQ(expectedResponse, std::string(connection.dataReceived.begin(), connection.dataReceived.end()));
// }
