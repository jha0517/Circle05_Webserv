/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UriTests.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 15:43:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/03 22:24:19 by hyunah           ###   ########.fr       */
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
