/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ConfigTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:32:26 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 16:19:23 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtest/gtest.h>
#include "../include/Config.hpp"

TEST(ConfigTests, ParseString1){
	Config config;

	std::string	rawMsg = {
	"server{\n"
	"	listen	8000;\n"
	"	root /home/hyunah/Desktop/mysite;\n"
	"	host 127.0.0.1;\n"
	"	error_page 404 /error/404.html;\n"

	"	location /fruits {\n"
	"			root /home/hyunah/Desktop/mysite;\n"
	"	}\n"
	};
	ASSERT_TRUE(config.parseFromString(rawMsg));
	ASSERT_EQ(1, config.getServerSize());
}
