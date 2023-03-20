/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:27 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/20 04:02:08 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _root(""), _autoindex(""), _default_err_page(""),
			_server_keyword_check(0), _server_block(0), _location_block(0)
{
}

Parse::Parse(std::string config_file): _root(""), _autoindex(""), _default_err_page(""),
			_server_keyword_check(0), _server_block(0), _location_block(0)
{
	FileOpen(config_file);
}

Parse::Parse(const Parse& parse): HttpBlockParse(parse)
{
	*this = parse;
}

Parse& Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	return (*this);
}

Parse::~Parse()
{
}

const char*	Parse::FileOpenFailedException::what(void) const throw()
{
	return ("File open error");
}

// const char*	Parse::InvalidServerBlockException::what(void) const throw()
// {
// 	return ("Invalid config file: server block");
// }

// void	Parse::ServerBlockCheck(std::string *line)
// {
// 	std::string	temp = *line;

// 	if (!_http_parse_done)
// 		return ;
// 	if (temp.find("server") != std::string::npos)
// 	{
// 		if (temp.find("server") != 0)
// 			temp = temp.substr(temp.find("server"), std::string::npos);
// 		_server_keyword_check++;
// 	}
// 	else if (temp.find("{") != std::string::npos)
// 	{
// 		if (temp.find("{") != 0)
// 			temp = temp.substr(temp.find("{"), std::string::npos);
// 		if (_server_keyword_check == 1)
// 		{
// 			this->_server_block++;
// 			_server_keyword_check--;
// 		}
// 	}
// 	else if (temp.find("listen") != std::string::npos
// 		|| temp.find("host") != std::string::npos
// 		|| temp.find("client_max_body_size") != std::string::npos
// 		|| temp.find("index") != std::string::npos
// 		|| temp.find("allow_methods") != std::string::npos
// 		|| temp.find("return") != std::string::npos
// 		|| temp.find("{") != std::string::npos
// 		|| temp.find("}") != std::string::npos
// 		|| temp.find("root") != std::string::npos
// 		|| temp.find("cgi") != std::string::npos)
// 	{
// 		return ;
// 	}
// 	else
// 	{
// 		for (int i = 0; i < (int)temp.length(); i++)
// 		{
// 			if (!(temp[i] == ' ' || temp[i] == '\t'))
// 			{
// 				std::cout << "error" << std::endl;
// 				std::cout << "temp: " << temp << std::endl;
// 				throw (InvalidServerBlockException());
// 			}
// 		}
// 		return ;
// 	}
// }

int	Parse::FileOpen(std::string config_file)
{
	std::fstream	f_read;

	f_read.open(config_file.c_str(), std::ios::in);
	if (f_read.fail())
	{
		throw (FileOpenFailedException());
		return (1);
	}

	std::string	line;
	int		i = 0;
	while (std::getline(f_read, line))
	{
		if (line[0] == '#' || line == "")
			continue ;
		if (line.find("#"))
			line = line.substr(0, line.find("#"));
		if (!HttpBlockParse::_http_parse_done)
		{
			HttpBlockParse::HttpBlockCheck(&line);
			HttpBlockParse::HttpBlockElementCheck(&line);
		}
		//else
		//	ServerBlockCheck(&line);
		//std::cout << "i: " << i << line << std::endl;
		i++;
	}

	if (!(HttpBlockParse::GetRoot() != ""
		&& HttpBlockParse::GetAutoIndex() != ""
		&& HttpBlockParse::GetDefaultErrorPage() != ""))
	{
		if (HttpBlockParse::GetRoot() == "")
			throw (MissedRootException());
		else if (HttpBlockParse::GetAutoIndex() == "")
			throw (MissedAutoIdxException());
		else if (HttpBlockParse::GetDefaultErrorPage() == "")
			throw (MissedErrPageException());
	}
	else
	{
		this->_root = HttpBlockParse::GetRoot();
		this->_autoindex = HttpBlockParse::GetAutoIndex();
		this->_default_err_page = HttpBlockParse::GetDefaultErrorPage();
		this->_err_page_directory = HttpBlockParse::GetErrPageDirectory();
	}
	
	
	
	
	std::cout << "root: " << this->_root << std::endl;
	std::cout << "autoindex: " << this->_autoindex << std::endl;
	std::cout << "default_err_page: " << this->_default_err_page << std::endl;
	std::cout << "err_page_directory: " << this->_err_page_directory << std::endl;
	std::cout << std::endl;

	std::cout << "server_block: " << _server_block << std::endl;
	std::cout << "location_block: " << _location_block << std::endl;

	std::cout << "http block: " << HttpBlockParse::_http_block << std::endl;
	
	f_read.close();
	return (0);
}
