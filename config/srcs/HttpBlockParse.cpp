/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBlockParse.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:52:58 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:20:56 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/HttpBlockParse.hpp"

HttpBlockParse::HttpBlockParse()
			: _http_keyword_check(0), _http_braket_open(0), _http_block(0),
			_root_flag(0), _root(""), _autoindex_flag(0), _autoindex(""),
			_default_err_page_flag(0), _default_err_page(""),
			_err_page_directory(""), _http_parse_done(0),
			_config_file_name(""), _err_msg("")
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
	this->_config_file_name = httpblockparse._config_file_name;
	this->_err_msg = httpblockparse._err_msg;
	return (*this);
}

HttpBlockParse::~HttpBlockParse()
{
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

void	HttpBlockParse::SetConfigFileName(std::string config_file_name)
{
	this->_config_file_name = config_file_name;
}

void	HttpBlockParse::HttpBlockCheck(std::string *line, int i)
{
	std::cout << "HTTP_BLOCK: ";
	std::string	temp = *line;
	
	if (temp.find("server") != std::string::npos)
		this->_http_parse_done++;
	if (this->_http_parse_done)
		return ;
	if (temp.find("}") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_CLOSE, *line, i);
		throw (this->_err_msg);
	}
	if (this->_http_braket_open && temp.find("{") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}

	if (temp.find("http") != std::string::npos)
	{
		if (temp.find("http") != 0 && !StringCheck(temp.substr(0, temp.find("http"))))
			temp = temp.substr(temp.find("http"), std::string::npos);
		if (std::strncmp("http", temp.c_str(), 4))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_HTTP, *line, i);
			throw (this->_err_msg);
		}
		this->_http_keyword_check++;
		if (this->_http_keyword_check == 0 && StringCheck(temp.substr(temp.find("http") + 4, std::string::npos), '{'))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("{") != std::string::npos)
		{
			this->_http_braket_open++;
			if (temp.find("{") != 0 && !StringCheck(temp.substr(0, temp.find("{"))))
				temp = temp.substr(temp.find("{"), std::string::npos);
			if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
			{
				this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_OPEN, *line, i);
				throw (this->_err_msg);
			}
			if (this->_http_keyword_check == 1 && this->_http_braket_open == 1)
			{
				this->_http_block++;
				this->_http_keyword_check--;
				this->_http_braket_open++;
			}
			else
			{
				this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_OPEN, *line, i);
				throw (this->_err_msg);
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
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);

		}
		if (StringCheck(temp.substr(temp.find("{") + 1, std::string::npos))
			&& !(temp.find("root") != std::string::npos
				|| temp.find("autoindex") != std::string::npos
				|| temp.find("default_error_page") != std::string::npos))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_INVALID_KWD, *line, i);
			throw (this->_err_msg);
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
	{
		return ;
	}
	else
	{
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (!(temp[i] == ' ' || temp[i] == '\t'))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, HTTP_INVALID_KWD, *line, i);
				throw (this->_err_msg);
			}
		}
		return ;
	}
}

void	HttpBlockParse::HttpBlockKeywordCheck(std::string *line, int i)
{
	std::string	temp = *line;
	std::string	token[100] = {"", };

	if (temp.find("http") != std::string::npos)
		temp = temp.substr(temp.find("http") + 4, std::string::npos);
	if (temp.find("root") != std::string::npos)
	{
		if (temp.find("root") != 0 && !StringCheck(temp.substr(0, temp.find("root")), '{'))
			temp = temp.substr(temp.find("root"), std::string::npos);
		if (TokenCount(2, temp, token) && !this->_http_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_ROOT, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("autoindex") != std::string::npos)
	{
		if (temp.find("autoindex") != 0 && !StringCheck(temp.substr(0, temp.find("autoindex")), '{'))
			temp = temp.substr(temp.find("autoindex"), std::string::npos);
		if (TokenCount(2, temp, token) && !this->_http_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_AUTOINDEX, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("default_error_page") != std::string::npos)
	{
		if (temp.find("default_error_page") != 0 && !StringCheck(temp.substr(0, temp.find("default_error_page")), '{'))
			temp = temp.substr(temp.find("default_error_page"), std::string::npos);
		if (TokenCount(2, temp, token) && !this->_http_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_DEFAULT_ERROR_PAGE, *line, i);
			throw (this->_err_msg);
		}
	}
	HttpBlockGetInfo(token, line, i);
	if (this->_root != "" && this->_autoindex != "" && this->_default_err_page != "")
		this->_http_parse_done = 1;
	if (this->_http_parse_done && !this->_http_braket_open)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, HTTP_BRAKET_OPEN);
		throw (this->_err_msg);
	}
	//add error check if keyword exists multiple times
}

void	HttpBlockParse::HttpBlockGetInfo(std::string *token, std::string *line, int i)
{
	if (token[0] == "root" && !_http_parse_done)
	{
		//if (CheckValidPath(token[1]))
		//	return (1);
		//check if the path is valid
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_root_flag++;
		this->_root = token[1].substr(0, token[1].length() - 1);
	}
	if (token[0] == "autoindex" && !_http_parse_done)
	{
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		if (!(token[1] == "on;" || token[1] == "off;"))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_KWD_AUTOINDEX, *line, i);
			throw (this->_err_msg);
		}
		this->_autoindex_flag++;
		this->_autoindex = token[1].substr(0, token[1].length() - 1);
	}
	if (token[0] == "default_error_page" && !_http_parse_done)
	{
		//if (CheckValidErrorPage(token[1]))
		//	return (1);
		//check if the path is valid
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_default_err_page_flag++;
		this->_default_err_page = this->_root + token[1].substr(0, token[1].length() - 1);

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
}
