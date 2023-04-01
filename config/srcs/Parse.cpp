/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:27 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/01 07:47:46 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _root(""), _autoindex(""), _default_err_page(""),
			_server_block_count(0), _location_block_count(0),
			_config_file_name(""), _err_msg("")
{
}

Parse::Parse(std::string config_file_name)
			: _root(""), _autoindex(""), _default_err_page(""),
			_server_block_count(0), _location_block_count(0),
			_config_file_name(""), _err_msg("")
{
	this->_config_file_name = config_file_name;
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

		if (!HttpBlockParse::GetHttpParseDone())
			HttpBlockParse::HttpBlockCheck(&line, i);
		else if (!ServerBlockParse::GetServerParseDone())
			ServerBlockParse::ServerBlockCheck(&line, i);
		else if (!LocationBlockParse::GetLocationParseDone())
			LocationBlockParse::LocationBlockCheck(&line, i);
			
		
		std::cout << "i: " << i << line << std::endl;
	}

	if (!LocationBlockParse::GetServerBraketClose())
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_CLOSE, line, i);
		throw (this->_err_msg);
	}
	if (!ServerBlockParse::GetHttpBraketClose())
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_CLOSE, line, i);
		throw (this->_err_msg);
	}
	
	this->_root = HttpBlockParse::GetRoot();
	this->_autoindex = HttpBlockParse::GetAutoIndex();
	this->_default_err_page = HttpBlockParse::GetDefaultErrorPage();
	this->_err_page_directory = HttpBlockParse::GetErrPageDirectory();

	this->_listen = ServerBlockParse::GetListen();
	this->_host = ServerBlockParse::GetHost();
	this->_client_max_body_size = ServerBlockParse::GetClientMaxBodySize();
	this->_index = ServerBlockParse::GetIndex();
	this->_allow_methods_get = ServerBlockParse::GetAllowMethodsGet();
	this->_allow_methods_post = ServerBlockParse::GetAllowMethodsPost();
	this->_allow_methods_delete = ServerBlockParse::GetAllowMethodsDelete();
	this->_server_block_count = ServerBlockParse::GetServerBlockCount();

	
	std::cout << std::endl;
	std::cout << "root: " << this->_root << std::endl;
	std::cout << "autoindex: " << this->_autoindex << std::endl;
	std::cout << "default_err_page: " << this->_default_err_page << std::endl;
	std::cout << "err_page_directory: " << this->_err_page_directory << std::endl;
	std::cout << std::endl;

	std::cout << "server_block: " << this->_server_block_count << std::endl;
	std::cout << "listen: " << this->_listen << std::endl;
	std::cout << "host: " << this->_host << std::endl;
	std::cout << "client_max_body_size: " << this->_client_max_body_size << std::endl;
	std::cout << "index: " << this->_index << std::endl;
	std::cout << "allow_methods: ";
	if (this->_allow_methods_get && !this->_allow_methods_post && !this->_allow_methods_delete)
		std::cout << "GET" << std::endl;
	else if (this->_allow_methods_get && this->_allow_methods_post && !this->_allow_methods_delete)
		std::cout << "GET POST" << std::endl;
	else if (this->_allow_methods_get && !this->_allow_methods_post && this->_allow_methods_delete)
		std::cout << "GET DELETE" << std::endl;
	else
		std::cout << "GET POST DELETE" << std::endl;
	std::cout << std::endl;


	std::cout << "location_block: " << LocationBlockParse::GetLocationBlockCount() << std::endl;
	(void)_location_block_count;
	
	f_read.close();
	return (0);
}
