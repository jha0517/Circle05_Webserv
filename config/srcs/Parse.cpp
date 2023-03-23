/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:27 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:22:27 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _root(""), _autoindex(""), _default_err_page(""),
			_server_block(0), _location_block(0),
			_config_file_name(""), _err_msg("")
{
}

Parse::Parse(std::string config_file_name)
			: _root(""), _autoindex(""), _default_err_page(""),
			_server_block(0), _location_block(0),
			_config_file_name(""), _err_msg("")
{
	this->_config_file_name = config_file_name;
	FileOpen(config_file_name);
}

//Parse::Parse(const Parse& parse): HttpBlockParse(parse), ServerBlockParse(parse)
Parse::Parse(const Parse& parse): ServerBlockParse(parse)
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

const char*	Parse::FileOpenFailedException::what(void) const throw()
{
	return ("File open error");
}

int	Parse::FileOpen(std::string config_file_name)
{
	std::fstream	f_read;

	f_read.open(config_file_name.c_str(), std::ios::in);
	if (f_read.fail())
	{
		throw (FileOpenFailedException());
		return (1);
	}

	HttpBlockParse::SetConfigFileName(config_file_name);
	ServerBlockParse::SetConfigFileName(config_file_name);

	std::string	line;
	int		i = 0;
	while (std::getline(f_read, line))
	{
		i++;
		if (line[0] == '#' || line == "")
			continue ;
		if (line.find("#"))
			line = line.substr(0, line.find("#"));
		if (!HttpBlockParse::_http_parse_done)
		{
			HttpBlockParse::HttpBlockCheck(&line, i);
			HttpBlockParse::HttpBlockKeywordCheck(&line, i);
		}
		else if (!ServerBlockParse::_server_parse_done)
		{
			ServerBlockParse::ServerBlockCheck(&line, i);
			ServerBlockParse::ServerBlockKeywordCheck(&line, i);
		}
		std::cout << "i: " << i << line << std::endl;
	}

	if (!(HttpBlockParse::GetRoot() != ""
		&& HttpBlockParse::GetAutoIndex() != ""
		&& HttpBlockParse::GetDefaultErrorPage() != ""))
	{
		if (HttpBlockParse::GetRoot() == "")
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_ROOT_MISSED);
			throw (this->_err_msg);
		}
		else if (HttpBlockParse::GetAutoIndex() == "")
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_AUTOINDEX_MISSED);
			throw (this->_err_msg);
		}
		else if (HttpBlockParse::GetDefaultErrorPage() == "")
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_DEFAULT_ERROR_PAGE_MISSED);
			throw (this->_err_msg);
		}
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

	std::cout << "server_block: " << ServerBlockParse::_server_block << std::endl;
	std::cout << "listen: " << ServerBlockParse::_listen << std::endl;
	std::cout << "host: " << ServerBlockParse::_host << std::endl;
	std::cout << "client_max_body_size: " << ServerBlockParse::_client_max_body_size << std::endl;
	std::cout << "index: " << ServerBlockParse::_index << std::endl;
	std::cout << "allow_methods: ";
	if (ServerBlockParse::_allow_methods_get && !ServerBlockParse::_allow_methods_post && !ServerBlockParse::_allow_methods_delete)
		std::cout << "GET" << std::endl;
	else if (ServerBlockParse::_allow_methods_get && ServerBlockParse::_allow_methods_post && !ServerBlockParse::_allow_methods_delete)
		std::cout << "GET POST" << std::endl;
	else
		std::cout << "GET POST DELETE" << std::endl;
	std::cout << std::endl;

	std::cout << "location_block: " << _location_block << std::endl;
	
	f_read.close();
	return (0);
}
