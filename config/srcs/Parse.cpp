/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:27 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/19 21:47:16 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

Parse::Parse(): _http_keyword_check(0), _http_braket_open(0), _http_block(0), _root_flag(0), _root(""),
			_autoindex_flag(0), _autoindex(""),
			_default_err_page_flag(0), _default_err_page(""), _http_parse_done(0),
			_server_keyword_check(0), _server_block(0), _location_block(0)
{
}

Parse::Parse(std::string config_file): _http_keyword_check(0), _http_braket_open(0), _http_block(0), _root_flag(0), _root(""),
			_autoindex_flag(0), _autoindex(""),
			_default_err_page_flag(0), _default_err_page(""), _http_parse_done(0),
			_server_keyword_check(0), _server_block(0), _location_block(0)
{
	FileOpen(config_file);
}

Parse::Parse(const Parse& parse)
{
	*this = parse;
}

Parse& Parse::operator=(const Parse& parse)
{
	if (this == &parse)
		return (*this);
	this->_http_block = parse._http_block;
	this->_server_block = parse._server_block;
	this->_location_block = parse._location_block;
	return (*this);
}

Parse::~Parse()
{
}

const char*	Parse::FileOpenFailedException::what(void) const throw()
{
	return ("File open error");
}

const char*	Parse::InvalidHttpBlockException::what(void) const throw()
{
	return ("Invalid cofig file: http block");
}

const char*	Parse::InvalidServerBlockException::what(void) const throw()
{
	return ("Invalid cofig file: server block");
}

std::string	Parse::ReplaceLine(std::string line, std::string s1, std::string s2)
{
	std::string	new_line = "";
	int		pos = 0;
	int		find = 0;

	while (1)
	{
		find = line.find(s1, pos);
		if (find == -1)
		{
			new_line += line.substr(pos, std::string::npos);
			break ;
		}
		new_line += line.substr(pos, find - pos);
		new_line += s2;
		pos += (find - pos + s1.length());
	}
	return (new_line);
}

int	Parse::CheckValidPath(std::string path)
{
	if (path == "./;")
		return (1);
	if (path[path.length() - 1] != ';')
		return (1);
	//check path later
	return (0);
}

int	Parse::CheckValidErrorPage(std::string path)
{
	std::string	err_path;

	if (path[path.length() - 1] != ';')
		return (1);
	err_path = _root + path;
	(void)err_path;
	//check error path later;
	return (0);
}

int	Parse::GetInfo(std::string key, std::string value)
{
	if (key == "root" && !_http_parse_done)
	{
		if (CheckValidPath(value))
			return (1);
		this->_root_flag++;
		this->_root = value.substr(0, value.length() - 1);
	}
	if (key == "autoindex" && !_http_parse_done)
	{
		if (!(value == "on;" || value == "off;"))
			return (1);
		this->_autoindex_flag++;
		this->_autoindex = value.substr(0, value.length() - 1);
	}
	if (key == "default_error_page" && !_http_parse_done)
	{
		if (CheckValidErrorPage(value))
			return (1);
		this->_default_err_page_flag++;
		this->_default_err_page = _root + value.substr(0, value.length() - 1);
	}
	return (0);
}

int	Parse::TokenCount(int n, std::string line)
{
	std::string	element[100] = {"",};
	int		i = 0;

	line = ReplaceLine(line, "\t", " ");
	std::stringstream	ss(line);
	while (!ss.eof())
	{
		getline(ss, element[i], ' ');
		if (element[i] == "")
			continue ;
		i++;
	}
	if (i != n)
		return (1);
	if (n == 2)
	{
		if (GetInfo(element[0], element[1]))
			return (1);
	}
	return (0);
}

void	Parse::HttpBlockElementCheck(std::string *line)
{
	std::string	temp = *line;

	if (temp.find("root") != std::string::npos)
	{
		if (temp.find("root") != 0)
			temp = temp.substr(temp.find("root"), std::string::npos);
		if (TokenCount(2, temp) && _server_block == 0)
			throw (InvalidHttpBlockException());
		
	}
	else if (temp.find("autoindex") != std::string::npos)
	{
		if (temp.find("autoindex") != 0)
			temp = temp.substr(temp.find("autoindex"), std::string::npos);
		if (TokenCount(2, temp) && _server_block == 0)
			throw (InvalidHttpBlockException());
	}
	else if (temp.find("default_error_page") != std::string::npos)
	{
		if (temp.find("default_error_page") != 0)
			temp = temp.substr(temp.find("default_error_page"), std::string::npos);
		if (TokenCount(2, temp) && _server_block == 0)
			throw (InvalidHttpBlockException());
	}
	if (_root != "" && _autoindex != "" && _default_err_page != "")
		_http_parse_done = 1;
	
}

void	Parse::HttpBlockCheck(std::string *line)
{
	std::string	temp = *line;
	
	if (_http_parse_done)
		return ;
	std::cout << "HTTP BLOCK: ";
	if (temp.find("http") != std::string::npos)
	{
		if (temp.find("http") != 0)
			temp = temp.substr(temp.find("http"), std::string::npos);
		_http_keyword_check++;
		if (temp.find("{") != std::string::npos)
		{
			_http_braket_open++;
			if (temp.find("{") != 0)
				temp = temp.substr(temp.find("{"), std::string::npos);
			if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
				throw (InvalidHttpBlockException());
			if (_http_keyword_check == 1 && _http_braket_open == 1)
			{
				this->_http_block++;
				_http_keyword_check--;
				_http_braket_open++;
			}
			else
				throw (InvalidHttpBlockException());
		}
	}
	else if (temp.find("{") != std::string::npos)
	{
		_http_braket_open++;
		if (temp.find("{") != 0)
			temp = temp.substr(temp.find("{"), std::string::npos);
		if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
			throw (InvalidHttpBlockException());
		if (_http_keyword_check == 1 && _http_braket_open == 1)
		{
			this->_http_block++;
			_http_keyword_check--;
			_http_braket_open++;
		}
		else
			throw (InvalidHttpBlockException());
	}
	else if (temp.find("root") != std::string::npos
		|| temp.find("autoindex") != std::string::npos
		|| temp.find("default_error_page") != std::string::npos)
		return ;
	else
	{
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (!(temp[i] == ' ' || temp[i] == '\t'))
				throw (InvalidHttpBlockException());
		}
		return ;
	}
}

void	Parse::ServerBlockCheck(std::string *line)
{
	std::string	temp = *line;

	if (!_http_parse_done)
		return ;
	if (temp.find("server") != std::string::npos)
	{
		if (temp.find("server") != 0)
			temp = temp.substr(temp.find("server"), std::string::npos);
		_server_keyword_check++;
	}
	else if (temp.find("{") != std::string::npos)
	{
		if (temp.find("{") != 0)
			temp = temp.substr(temp.find("{"), std::string::npos);
		if (_server_keyword_check == 1)
		{
			this->_server_block++;
			_server_keyword_check--;
		}
	}
	else if (temp.find("listen") != std::string::npos
		|| temp.find("host") != std::string::npos
		|| temp.find("client_max_body_size") != std::string::npos
		|| temp.find("index") != std::string::npos
		|| temp.find("allow_methods") != std::string::npos
		|| temp.find("return") != std::string::npos
		|| temp.find("{") != std::string::npos
		|| temp.find("}") != std::string::npos
		|| temp.find("root") != std::string::npos
		|| temp.find("cgi") != std::string::npos)
	{
		return ;
	}
	else
	{
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (!(temp[i] == ' ' || temp[i] == '\t'))
			{
				std::cout << "error" << std::endl;
				std::cout << "temp: " << temp << std::endl;
				throw (InvalidServerBlockException());
			}
		}
		return ;
	}
}

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
		if (!_http_parse_done)
		{
			HttpBlockCheck(&line);
			HttpBlockElementCheck(&line);
		}
		else
			ServerBlockCheck(&line);
		std::cout << "i: " << i << line << std::endl;
		i++;
	}
	
	if (_http_block != 1 || _root_flag != 1 || _autoindex_flag != 1)
		throw (InvalidHttpBlockException());
	
	std::cout << "http_block: " << _http_block << std::endl;
	std::cout << "root_flag: " << _root_flag << std::endl;
	std::cout << "root: " << _root << std::endl;
	std::cout << "autoindex_flag: " << _autoindex_flag << std::endl;
	std::cout << "autoindex: " << _autoindex << std::endl;
	std::cout << "default_err_page_flag: " << _default_err_page_flag << std::endl;
	std::cout << "default_err_page: " << _default_err_page << std::endl;
	std::cout << std::endl;
	std::cout << "server_block: " << _server_block << std::endl;
	std::cout << "location_block: " << _location_block << std::endl;
	
	f_read.close();
	return (0);
}
