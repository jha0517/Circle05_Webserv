/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostin <acostin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:27 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/03 02:17:17 by acostin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _total_server_block(0)
{
}

Parse::Parse(std::string config_file_name): _total_server_block(0)
{
	FileOpen(config_file_name);
}

Parse::Parse(const Parse& parse): LocationBlockParse(parse)
{
	*this = parse;
}

Parse& Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	
	//edit here later
	return (*this);
}

Parse::~Parse()
{
}

int	Parse::FileOpen(std::string config_file_name)
{
	std::fstream	f_read;

	f_read.open(config_file_name.c_str(), std::ios::in);
	if (f_read.fail())
	{
		std::string	err_msg = ErrMsg("", FILE_OPEN_ERROR, "", -1);
		throw (err_msg);
		return (1);
	}

	HttpBlockParse::SetConfigFileName(config_file_name);
	ServerBlockParse::SetConfigFileName(config_file_name);
	LocationBlockParse::SetConfigFileName(config_file_name);

	std::string	line;
	int		i = 0;
	while (std::getline(f_read, line))
	{
		i++;
		if (line[0] == '#' || line == "")
			continue ;
		if (line.find("#"))
			line = line.substr(0, line.find("#"));

		if (!HttpBlockParse::GetHttpParseDone())
			HttpBlockParse::HttpBlockCheck(&line, i);
		else if (!ServerBlockParse::GetServerParseDone())
			ServerBlockParse::ServerBlockCheck(&line, i);
		else if (!LocationBlockParse::GetLocationParseDone())
			LocationBlockParse::LocationBlockCheck(&line, i);
			
		
		std::cout << line << std::endl;
	}

	this->_total_server_block = ServerBlockParse::GetServerBlockCount();
	std::cout << std::endl << CYAN
		<< "total server block: " << this->_total_server_block << BLACK << std::endl;
	
	f_read.close();
	return (0);
}
