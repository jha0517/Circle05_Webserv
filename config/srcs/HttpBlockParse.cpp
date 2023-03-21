/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBlockParse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:52:58 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/20 04:21:55 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpBlockParse.hpp"

HttpBlockParse::HttpBlockParse(): _http_keyword_check(0), _http_braket_open(0), _http_block(0),
			_root_flag(0), _root(""), _autoindex_flag(0), _autoindex(""),
			_default_err_page_flag(0), _default_err_page(""),
			_err_page_directory(""), _http_parse_done(0)
{
}

HttpBlockParse::HttpBlockParse(const HttpBlockParse& httpblockparse)
{
	*this = httpblockparse;
}

HttpBlockParse& HttpBlockParse::operator=(const HttpBlockParse& httpblockparse)
{
	if (this == &httpblockparse)
		return (*this);
	this->_http_keyword_check = httpblockparse._http_keyword_check;
	this->_http_braket_open = httpblockparse._http_braket_open;
	this->_http_block = httpblockparse._http_block;
	this->_root_flag = httpblockparse._root_flag;
	this->_root = httpblockparse._root;
	this->_autoindex_flag = httpblockparse._autoindex_flag;
	this->_autoindex = httpblockparse._autoindex;
	this->_default_err_page_flag = httpblockparse._default_err_page_flag;
	this->_default_err_page = httpblockparse._default_err_page;
	this->_err_page_directory = httpblockparse._err_page_directory;
	this->_http_parse_done = httpblockparse._http_parse_done;
	return (*this);
}

HttpBlockParse::~HttpBlockParse()
{
}

const char*	HttpBlockParse::InvalidBraketOpenException::what(void) const throw()
{
	return ("Invalid config file: HttpBlock: '{' is missed or not opened properly");
}

const char*	HttpBlockParse::InvalidKwdHttpException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword http");
}

const char*	HttpBlockParse::InvalidKwdRootException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword root");
}

const char*	HttpBlockParse::InvalidKwdAutoIdxException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword autoindex");
}

const char*	HttpBlockParse::InvalidKwdErrPageException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword _default_error_page");
}

const char*	HttpBlockParse::MissedRootException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword root is missed");
}

const char*	HttpBlockParse::MissedAutoIdxException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword autoindex is missed");
}

const char*	HttpBlockParse::MissedErrPageException::what(void) const throw()
{
	return ("Invalid config file: Http block: keyword _default_error_page is missed");
}

const char*	HttpBlockParse::InvalidCharacterException::what(void) const throw()
{
	return ("Invalid config file: Http block: found invalid character");
}

std::string	HttpBlockParse::GetRoot(void) const
{
	return (this->_root);
}

std::string	HttpBlockParse::GetAutoIndex(void) const
{
	return (this->_autoindex);
}

std::string	HttpBlockParse::GetDefaultErrorPage(void) const
{
	return (this->_default_err_page);
}

std::string	HttpBlockParse::GetErrPageDirectory(void) const
{
	return (this->_err_page_directory);
}

void	HttpBlockParse::HttpBlockElementCheck(std::string *line)
{
	std::string	temp = *line;

	if (temp.find("root") != std::string::npos)
	{
		if (temp.find("root") != 0 && !StringCheck(temp.substr(0, temp.find("root")), '{'))
			temp = temp.substr(temp.find("root"), std::string::npos);
		if (TokenCount(2, temp) && !_http_parse_done)
		{
			std::cout << *line << std::endl;
			throw (InvalidKwdRootException());
		}
	}
	else if (temp.find("autoindex") != std::string::npos)
	{
		if (temp.find("autoindex") != 0 && !StringCheck(temp.substr(0, temp.find("autoindex")), '{'))
			temp = temp.substr(temp.find("autoindex"), std::string::npos);
		if (TokenCount(2, temp) && !_http_parse_done)
		{
			std::cout << *line << std::endl;
			throw (InvalidKwdAutoIdxException());
		}
	}
	else if (temp.find("default_error_page") != std::string::npos)
	{
		if (temp.find("default_error_page") != 0 && !StringCheck(temp.substr(0, temp.find("default_error_page"))), '{')
			temp = temp.substr(temp.find("default_error_page"), std::string::npos);
		if (TokenCount(2, temp) && !_http_parse_done)
		{
			std::cout << *line << std::endl;
			throw (InvalidKwdErrPageException());
		}
	}
	if (this->_root != "" && this->_autoindex != "" && this->_default_err_page != "")
		this->_http_parse_done = 1;
	if (this->_http_parse_done && !this->_http_braket_open)
		throw (InvalidBraketOpenException());
}

void	HttpBlockParse::HttpBlockCheck(std::string *line)
{
	std::string	temp = *line;
	
	if (temp.find("server") != std::string::npos)
		this->_http_parse_done++;
	if (this->_http_parse_done)
		return ;
	if (temp.find("http") != std::string::npos)
	{
		if (temp.find("http") != 0 && !StringCheck(temp.substr(0, temp.find("http"))))
			temp = temp.substr(temp.find("http"), std::string::npos);
		if (std::strncmp("http", temp.c_str(), 4) || StringCheck(temp.substr(temp.find("http") + 4, std::string::npos), '{'))
		{
			std::cout << *line << std::endl;
			throw (InvalidKwdHttpException());
		}
		this->_http_keyword_check++;
		if (temp.find("{") != std::string::npos)
		{
			this->_http_braket_open++;
			if (temp.find("{") != 0 && !StringCheck(temp.substr(0, temp.find("{"))))
				temp = temp.substr(temp.find("{"), std::string::npos);
			if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
			{
				std::cout << *line << std::endl;
				throw (InvalidBraketOpenException());
			}
			if (this->_http_keyword_check == 1 && this->_http_braket_open == 1)
			{
				this->_http_block++;
				this->_http_keyword_check--;
				this->_http_braket_open++;
			}
			else
			{
				std::cout << *line << std::endl;
				throw (InvalidBraketOpenException());
			}
		}
	}
	else if (temp.find("{") != std::string::npos)
	{
		this->_http_braket_open++;
		if (temp.find("{") != 0)
			temp = temp.substr(temp.find("{"), std::string::npos);
		if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
		{
			std::cout << *line << std::endl;
			throw (InvalidBraketOpenException());
		}
		if (StringCheck(temp.substr(temp.find("{") + 1, std::string::npos))
			&& !(temp.find("root") != std::string::npos
				|| temp.find("autoindex") != std::string::npos
				|| temp.find("default_error_page") != std::string::npos))
		{
			std::cout << *line << std::endl;
			throw (InvalidCharacterException());
		}
		if (this->_http_keyword_check == 1 && this->_http_braket_open == 1)
		{
			this->_http_block++;
			this->_http_keyword_check--;
			this->_http_braket_open++;
		}
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
			{
				std::cout << *line << std::endl;
				throw (InvalidCharacterException());
			}
		}
		return ;
	}
}






static std::string	ReplaceLine(std::string line, std::string s1, std::string s2)
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

int	HttpBlockParse::CheckValidPath(std::string path)
{
	if (path == "./;")
		return (1);
	if (path[path.length() - 1] != ';')
		return (1);
	//check path later
	return (0);
}

int	HttpBlockParse::CheckValidErrorPage(std::string path)
{
	std::string	err_path;

	if (path[path.length() - 1] != ';')
		return (1);
	err_path = _root + path;
	(void)err_path;
	//check error path later;
	return (0);
}

int	HttpBlockParse::GetInfo(std::string key, std::string value)
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

		std::stringstream	ss(this->_default_err_page);
		std::string		word[100];
		int			i = 0;
		while (!ss.eof())
		{
			getline(ss, word[i], '/');
			i++;
		}
		std::string	err_page_directory = "";
		for (int j = 0; j < i - 1; j++)
		{
			err_page_directory.append(word[j]);
			if (j != i - 2)
				err_page_directory += '/';
		}
		this->_err_page_directory = err_page_directory;
	}
	return (0);
}

int	HttpBlockParse::TokenCount(int n, std::string line)
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
