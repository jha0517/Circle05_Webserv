/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UriTests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:43:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/04 23:12:29 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../include/Uri.hpp"

TEST(UriTests, ParseFromString){
	Uri uri;
	ASSERT_TRUE(uri.ParsingFromString("http://www.example.com/foo/bar"));
	ASSERT_EQ("http", uri.getScheme());
	ASSERT_EQ("www.example.com", uri.getHost());
	ASSERT_EQ(
		(std::vector<std::string>{
			"", 
			"foo", 
			"bar",
			}), 
			uri.getPath()
	);
	uri.setSplitChar(":");
	ASSERT_TRUE(uri.ParsingFromString("urn:book:fantasy:Hobbit"));
	ASSERT_EQ("urn", uri.getScheme());
	ASSERT_EQ("", uri.getHost());
	ASSERT_EQ(
		(std::vector<std::string>{
			"book", 
			"fantasy", 
			"Hobbit",
			}), 
			uri.getPath()
	);
}

TEST(UriTests, ParseFromStringNoPath){
	Uri uri;
	ASSERT_TRUE(uri.ParsingFromString("http://www.example.com"));
	ASSERT_EQ("http", uri.getScheme());
	ASSERT_EQ("www.example.com", uri.getHost());
	ASSERT_EQ(
		(std::vector<std::string>{}), 
			uri.getPath()
	);
}
TEST(UriTests, ParseFromStringMultiCharacter){
	Uri uri;

	uri.setSplitChar("/-");
	ASSERT_TRUE(uri.ParsingFromString("urn:book/-fant/asy/-Hobb-it"));
	ASSERT_EQ("urn", uri.getScheme());
	ASSERT_EQ("", uri.getHost());
	ASSERT_EQ(
		(std::vector<std::string>{
			"book", 
			"fant/asy", 
			"Hobb-it",
			}), 
			uri.getPath()
	);
}

TEST(UriTests, ParseFromStringPathCornerCases){
	// "/" -> [""]
	// ""  -> []
	// "foo/"  -> ["foo", ""]
	// "/foo"  -> ["", "foo"]	
	Uri uri;

	uri.setSplitChar("/");
	ASSERT_TRUE(uri.ParsingFromString("/"));
	ASSERT_EQ((std::vector<std::string> {""}), uri.getPath());

	ASSERT_TRUE(uri.ParsingFromString(""));
	ASSERT_EQ((std::vector<std::string> {}), uri.getPath());

	ASSERT_TRUE(uri.ParsingFromString("foo/"));
	ASSERT_EQ((std::vector<std::string> {"foo", ""}), uri.getPath());

	ASSERT_TRUE(uri.ParsingFromString("/foo"));
	ASSERT_EQ((std::vector<std::string> {"", "foo"}), uri.getPath());
}

TEST(UriTests, ParseFromStringHasPortNumber){
	Uri uri;

	ASSERT_TRUE(uri.ParsingFromString("http://www.lolo.com:8080/foo/bar"));
	ASSERT_EQ("www.lolo.com", uri.getHost());
	ASSERT_TRUE(uri.hasPort());
	ASSERT_EQ(8080, uri.getPort());
}

TEST(UriTests, ParseFromStringDoesNotPortNumber){
	Uri uri;

	ASSERT_TRUE(uri.ParsingFromString("http://www.lolo.com/foo/bar"));
	ASSERT_EQ("www.lolo.com", uri.getHost());
	ASSERT_FALSE(uri.hasPort());
}

TEST(UriTests, ParseFromStringFirstPortThenNoPort){
	Uri uri;

	ASSERT_TRUE(uri.ParsingFromString("http://www.lolo.com:8080/foo/bar"));
	ASSERT_EQ("www.lolo.com", uri.getHost());
	ASSERT_TRUE(uri.hasPort());
	ASSERT_EQ(8080, uri.getPort());
	ASSERT_TRUE(uri.ParsingFromString("http://www.lolo.com/foo/bar"));
	ASSERT_EQ("www.lolo.com", uri.getHost());
	ASSERT_FALSE(uri.hasPort());
}

TEST(UriTests, ParseFromStringBadPortNumber){
	Uri uri;

	ASSERT_FALSE(uri.ParsingFromString("http://www.lolo.com:spam/foo/bar"));
	ASSERT_FALSE(uri.ParsingFromString("http://www.lolo.com:spam8080/foo/bar"));
	ASSERT_FALSE(uri.ParsingFromString("http://www.lolo.com:8080spam/foo/bar"));
	ASSERT_FALSE(uri.ParsingFromString("http://www.lolo.com:99999999999999/foo/bar"));
	ASSERT_FALSE(uri.ParsingFromString("http://www.lolo.com:-1/foo/bar"));
	ASSERT_TRUE(uri.ParsingFromString("http://www.lolo.com:65535/foo/bar"));
	ASSERT_TRUE(uri.ParsingFromString("http://www.lolo.com:0/foo/bar"));
}


// TEST(UriTests, ParseFromStringIsRelativePath){
// 	Uri uri;

// 	ASSERT_TRUE(uri.ParsingFromString("htt://www.example.com/"));
// 	ASSERT_TRUE(uri.ParsingFromString("htt://www.example.com"));
// 	ASSERT_EQ("htt://www.example.com", false);
// 	ASSERT_EQ("htt://www.example.com/", false);
// 	ASSERT_EQ("/", true);
// 	ASSERT_EQ("foo", true);
// }
