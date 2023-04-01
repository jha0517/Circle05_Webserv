/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlockParse.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:19:53 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/01 17:36:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/LocationBlockParse.hpp"

LocationBlockParse::LocationBlockParse()
			: _location_keyword_check(0), _location_braket_open(0),
			_location_braket_close(0), _server_braket_close(0), _location_block_count(0),
			_redirection_flag(0), _return_flag(0),
			_cgi_bin_flag(0), _root_flag(0), _cgi_path_flag(0), _cgi_extention_flag(0),
			_redirection(""), _return(""), _root(""),
			_cgi_path_python(0), _cgi_path_bash(0), _cgi_path_php(0),
			_cgi_extention_py(0), _cgi_extention_sh(0), _cgi_extention_php(0),
			_location_parse_done(0), _config_file_name(""), _err_msg("")
{
}

LocationBlockParse::LocationBlockParse(const LocationBlockParse& locationblockparse)
			: ServerBlockParse(locationblockparse)
{
	*this = locationblockparse;
}

LocationBlockParse& LocationBlockParse::operator=(const LocationBlockParse& locationblockparse)
{
	if (this == &locationblockparse)
		return (*this);
	ServerBlockParse::operator=(locationblockparse);
	this->_location_keyword_check = locationblockparse._location_keyword_check;
	this->_location_braket_open = locationblockparse._location_braket_open;
	this->_location_braket_close = locationblockparse._location_braket_close;
	this->_server_braket_close = locationblockparse._server_braket_close;
	this->_location_block_count = locationblockparse._location_block_count;
	this->_redirection_flag = locationblockparse._redirection_flag;
	this->_return_flag = locationblockparse._return_flag;
	this->_cgi_bin_flag = locationblockparse._cgi_bin_flag;
	this->_root_flag = locationblockparse._root_flag;
	this->_cgi_path_flag = locationblockparse._cgi_path_flag;
	this->_cgi_extention_flag = locationblockparse._cgi_extention_flag;
	this->_redirection = locationblockparse._redirection;
	this->_return = locationblockparse._return;
	this->_root = locationblockparse._root;
	this->_cgi_path_python = locationblockparse._cgi_path_python;
	this->_cgi_path_bash = locationblockparse._cgi_path_bash;
	this->_cgi_path_php = locationblockparse._cgi_path_php;
	this->_cgi_extention_py = locationblockparse._cgi_extention_py;
	this->_cgi_extention_sh = locationblockparse._cgi_extention_sh;
	this->_cgi_extention_php = locationblockparse._cgi_extention_php;
	this->_location_parse_done = locationblockparse._location_parse_done;
	this->_config_file_name = locationblockparse._config_file_name;
	this->_err_msg = locationblockparse._err_msg;
	return (*this);
}

LocationBlockParse::~LocationBlockParse()
{
}

std::string	LocationBlockParse::GetRedirection(void) const
{
	return (this->_redirection);
}

std::string	LocationBlockParse::GetReturn(void) const
{
	return (this->_return);
}

std::string	LocationBlockParse::GetRoot(void) const
{
	return (this->_root);
}

int	LocationBlockParse::GetCgiPathPython(void) const
{
	return (this->_cgi_path_python);
}

int	LocationBlockParse::GetCgiPathBash(void) const
{
	return (this->_cgi_path_bash);
}

int	LocationBlockParse::GetCgiPathPhp(void) const
{
	return (this->_cgi_path_php);
}

int	LocationBlockParse::GetCgiExtentionPy(void) const
{
	return (this->_cgi_extention_py);
}

int	LocationBlockParse::GetCgiExtentionSh(void) const
{
	return (this->_cgi_extention_sh);
}

int	LocationBlockParse::GetCgiExtentionPhp(void) const
{
	return (this->_cgi_extention_php);
}

int	LocationBlockParse::GetLocationParseDone(void) const
{
	return (this->_location_parse_done);
}

int	LocationBlockParse::GetLocationBlockCount(void) const
{
	return (this->_location_block_count);
}

int	LocationBlockParse::GetServerBraketClose(void) const
{
	return (this->_server_braket_close);
}

void	LocationBlockParse::SetConfigFileName(std::string config_file_name)
{
	this->_config_file_name = config_file_name;
}

void	LocationBlockParse::LocationBlockCheck(std::string *line, int i)
{
	std::string	temp = *line;

	std::cout << "LOCATION_BLOCK: ";//
	ServerMissedKeywordCheck(line, temp, i);

	if (temp.find("location") != std::string::npos)
		LocationKeywordLocationCheck(line, temp, i);
	else if (temp.find("{") != std::string::npos)
		LocationBraketOpenCheck(line, temp, i);
	else if (temp.find("return") != std::string::npos
		|| temp.find("root") != std::string::npos
		|| temp.find("cgi_path") != std::string::npos
		|| temp.find("cgi_extention") != std::string::npos)
	{
		if (temp.find("return") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "return");
		if (temp.find("root") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "root");
		if (temp.find("cgi_path") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "cgi_path");
		if (temp.find("cgi_extention") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "cgi_extention");
		LocationKeywordTokenCheck(line, temp, i);
	}
	// else
	// {
	// 	if (StringCheck(temp))
	// 	{
	// 		this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_INVALID_KWD, *line, i);
	// 		throw (this->_err_msg);
	// 	}
	// }

	

	LocationBraketCloseCheck(line, temp, i);
}

void	LocationBlockParse::ServerMissedKeywordCheck(std::string *line, std::string temp, int i)
{
	if (ServerBlockParse::GetServerParseDone() && temp.find("location") == std::string::npos)
	{
		if (temp.find("listen") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_LISTEN_MISSED, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("host") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_HOST_MISSED, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("client_max_body_size") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_CLIENT_MAX_BODY_SIZE_MISSED, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("index") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_INDEX_MISSED, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("allow_methods") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS_MISSED, *line, i);
			throw (this->_err_msg);
		}
	}
	if (ServerBlockParse::GetListen() == 0)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_LISTEN_MISSED, *line, i);
		throw (this->_err_msg);
	}
	if (ServerBlockParse::GetHost() == "")
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_HOST_MISSED, *line, i);
		throw (this->_err_msg);
	}
	if (ServerBlockParse::GetClientMaxBodySize() == 0)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_CLIENT_MAX_BODY_SIZE_MISSED, *line, i);
		throw (this->_err_msg);
	}
	if (ServerBlockParse::GetIndex() == "")
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_INDEX_MISSED, *line, i);
		throw (this->_err_msg);
	}
	if (ServerBlockParse::GetAllowMethodsGet() == 0)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS_MISSED, *line, i);
		throw (this->_err_msg);
	}
}

void	LocationBlockParse::LocationKeywordCheck(std::string *line, std::string temp, int i, std::string keyword)
{
	if (StringCheck(temp.substr(0, temp.find(keyword)))
		|| !(temp[temp.find(keyword) + strlen(keyword.c_str())] == ' ' || temp[temp.find(keyword) + strlen(keyword.c_str())] == '\t'))
	{
		if (keyword == "location")
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_LOCATION, *line, i);
		else if (keyword == "/redirection")
		{
			if (temp[temp.find(keyword) + strlen(keyword.c_str())] == '\0')
				return ;
			if (temp[temp.find(keyword) + strlen(keyword.c_str())] == '/')
				return ;
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_REDIRECTION_PATH, *line, i);
		}
		else if (keyword == "return")
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_RETURN, *line, i);
		else if (keyword == "cgi-bin")
		{
			if (temp[temp.find(keyword) + strlen(keyword.c_str())] == '\0')
				return ;
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN, *line, i);
		}
		else if (keyword == "root")
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_ROOT, *line, i);
		else if (keyword == "cgi_path")
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH, *line, i);
		else if (keyword == "cgi_extention")
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION, *line, i);
		throw (this->_err_msg);
	}
}

void	LocationBlockParse::LocationKeywordLocationCheck(std::string *line, std::string temp, int i)
{
	if ((this->_location_keyword_check && this->_redirection_flag && this->_return_flag)
		|| (this->_location_keyword_check && this->_cgi_bin_flag
			&& this->_root_flag && this->_cgi_path_flag && this->_cgi_extention_flag))
	{
		if (!this->_location_braket_close)
		{
			std::cout << "missed closing braket" << std::endl;//
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_CLOSE, *line, i);
			throw (this->_err_msg);
		}
	}
	LocationKeywordCheck(line, temp, i, "location");
	this->_location_keyword_check++;
	if (this->_location_keyword_check == 0 && StringCheck(temp.substr(temp.find("location") + strlen("location"), std::string::npos), '{'))
	{
		this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}
	if (temp.find("/redirection") != std::string::npos
		|| temp.find("cgi-bin") != std::string::npos)
	{
		if (temp.find("/redirection") != std::string::npos)
		{
			std::string	tmp = temp.substr(temp.find("location") + strlen("location"), std::string::npos);
			LocationKeywordCheck(line, tmp, i, "/redirection");
			this->_redirection_flag++;
		}
		if (temp.find("cgi-bin") != std::string::npos)
		{
			std::string	tmp = temp.substr(temp.find("location") + strlen("location"), std::string::npos);
			LocationKeywordCheck(line, tmp, i, "cgi-bin");
			this->_cgi_bin_flag++;
		}
	}
	if (!(this->_redirection_flag || this->_cgi_bin_flag))
	{
		this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_LOCATION, *line, i);
		throw (this->_err_msg);
	}
	if (temp.find("{") != std::string::npos)
	{
		if (temp.find("/redirection/") != std::string::npos)
			temp = temp.substr(temp.find("/redirection/") + strlen("/redirection/"), std::string::npos);
		if (temp.find("/redirection") != std::string::npos)
			temp = temp.substr(temp.find("/redirection") + strlen("/redirection"), std::string::npos);
		if (temp.find("cgi-bin") != std::string::npos)
			temp = temp.substr(temp.find("cgi-bin") + strlen("cgi-bin"), std::string::npos);
		if (StringCheck(temp.substr(0, temp.find("{"))))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
		LocationBraketOpenCheck(line, temp, i);
	}
}

void	LocationBlockParse::LocationBraketOpenCheck(std::string *line, std::string temp, int i)
{
	this->_location_braket_open++;
	if (temp.find("{") != 0 && !StringCheck(temp.substr(0, temp.find("{"))))
		temp = temp.substr(temp.find("{"), std::string::npos);
	if (temp.substr(temp.find("{") + strlen("{"), std::string::npos).find("{") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}
	if (temp.find("return") != std::string::npos
		|| temp.find("root") != std::string::npos
		|| temp.find("cgi_path") != std::string::npos
		|| temp.find("cgi_extention") != std::string::npos)
	{
		temp = temp.substr(temp.find("{") + 1, std::string::npos);
		if (temp.find("return") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "return");
		if (temp.find("root") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "root");
		if (temp.find("cgi_path") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "cgi_path");
		if (temp.find("cgi_extention") != std::string::npos)
			LocationKeywordCheck(line, temp, i, "cgi_extention");
		LocationKeywordTokenCheck(line, temp, i);
	}
	if (temp.substr(temp.find("{") + strlen("{"), std::string::npos).find("}") != std::string::npos)
	{
		if (!(this->_redirection_flag && this->_return_flag))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
	}
}

void	LocationBlockParse::LocationKeywordTokenCheck(std::string *line, std::string temp, int i)
{
	std::string	token[100] = {"", };

	if (temp.find("return") != std::string::npos)
	{
		if (!this->_redirection_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_RETURN);
			throw (this->_err_msg);
		}
		if (!this->_location_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN);
			throw (this->_err_msg);
		}
		if (this->_return_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_RETURN_EXISTS);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_location_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_RETURN, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("root") != std::string::npos)
	{
		if (!this->_cgi_bin_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_ROOT);
			throw (this->_err_msg);
		}
		if (!this->_location_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN);
			throw (this->_err_msg);
		}
		if (this->_root_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_ROOT_EXISTS);
			throw (this->_err_msg);
		}
		if (TokenCount(2, temp, token) && !this->_location_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_ROOT, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("cgi_path") != std::string::npos)
	{
		if (!this->_cgi_bin_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH);
			throw (this->_err_msg);
		}
		if (!this->_location_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN);
			throw (this->_err_msg);
		}
		if (this->_cgi_path_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH_EXISTS);
			throw (this->_err_msg);
		}
		if (temp.find("python") != std::string::npos)
		{
			if (TokenCount(3, temp, token) && !this->_location_parse_done)
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH, *line, i);
				throw (this->_err_msg);
			}
		}
		else if (temp.find("php-cgi") != std::string::npos)
		{
			if (TokenCount(2, temp, token) && !this->_location_parse_done)
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH, *line, i);
				throw (this->_err_msg);
			}
		}
		else
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("cgi_extention") != std::string::npos)
	{
		if (!this->_cgi_bin_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION);
			throw (this->_err_msg);
		}
		if (!this->_location_braket_open)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_OPEN);
			throw (this->_err_msg);
		}
		if (this->_cgi_extention_flag)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION);
			throw (this->_err_msg);
		}
		if (temp.find("py") != std::string::npos)
		{
			if (TokenCount(3, temp, token) && !this->_location_parse_done)
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION, *line, i);
				throw (this->_err_msg);
			}
		}
		else if (temp.find("php") != std::string::npos)
		{
			if (TokenCount(2, temp, token) && !this->_location_parse_done)
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION, *line, i);
				throw (this->_err_msg);
			}
		}
		else
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION);
			throw (this->_err_msg);
		}
	}
	LocationBlockGetInfo(token, line, temp, i);
}

void	LocationBlockParse::LocationBlockGetInfo(std::string *token, std::string *line, std::string temp, int i)
{
	if (token[0] == "return" && !this->_location_parse_done)
	{
		//return value check
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_return_flag++;
		this->_return = token[1].substr(0, token[1].length() - 1);
	}
	if (token[0] == "root" && !this->_location_parse_done)
	{
		//check root
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_root_flag++;
		this->_root = token[1].substr(0, token[1].length() - 1);
	}
	if (token[0] == "cgi_path" && !this->_location_parse_done)
	{
		//edit later
		if (temp.find("python") != std::string::npos)
		{
			if (SemicolonCheck(token[2]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!((token[1] == "/usr/bin/python3" && token[2] == "/bin/bash;")
				|| (token[1] == "/bin/bash" && token[2] == "/usr/bin/python3;")))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH, *line, i);
				throw (this->_err_msg);
			}
			if (token[1] == "/usr/bin/python3" || token[2] == "/usr/bin/python3;")
				this->_cgi_path_python = 1;
			if (token[1] == "/bin/bash" || token[2] == "/bin/bash;")
				this->_cgi_path_bash = 1;
			this->_cgi_path_flag++;
		}
		else if (temp.find("php-cgi") != std::string::npos)
		{
			if (SemicolonCheck(token[1]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!(token[1] == "/usr/bin/php-cgi;"))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_PATH, *line, i);
				throw (this->_err_msg);
			}
			this->_cgi_extention_php = 1;
			this->_cgi_path_flag++;
		}
	}
	if (token[0] == "cgi_extention" && !this->_location_parse_done)
	{
		//edit later
		if (temp.find("py") != std::string::npos)
		{
			if (SemicolonCheck(token[2]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!((token[1] == ".py" && token[2] == ".sh;")
				|| (token[1] == ".sh" && token[2] == ".py;")))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION, *line, i);
				throw (this->_err_msg);
			}
			if (token[1] == ".py" || token[2] == ".py;")
				this->_cgi_extention_py = 1;
			if (token[1] == ".sh" || token[2] == ".sh;")
				this->_cgi_extention_sh = 1;
			this->_cgi_extention_flag++;
		}
		else if (temp.find("php") != std::string::npos)
		{
			if (SemicolonCheck(token[1]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!(token[1] == ".php;"))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_KWD_CGI_BIN_CGI_EXTENTION, *line, i);
				throw (this->_err_msg);
			}
			this->_cgi_extention_php = 1;
			this->_cgi_extention_flag++;
		}
	}
}

void	LocationBlockParse::LocationBraketCloseCheck(std::string *line, std::string temp, int i)
{
	//check element missing
	if (_location_braket_open == _location_braket_close + 1 && temp.find("}") != std::string::npos)
	{
		if (!((this->_redirection_flag && this->_return_flag)
			|| (this->_cgi_bin_flag && this->_root_flag && this->_cgi_path_flag && this->_cgi_extention_flag)))
		{
			std::cout << "error here" << std::endl;//
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_CLOSE, *line, i);
			throw (this->_err_msg);
		}
		std::cout << "location block closed" << std::endl;//
		_location_braket_close++;
		_location_block_count++;
		ServerBlockParse::IncreaseTotalLocationBlock();
		std::cout << "location block: " << ServerBlockParse::GetTotalLocationBlock() << std::endl;//
		if (!(this->_cgi_bin_flag && this->_root_flag && this->_cgi_path_flag && this->_cgi_extention_flag))
		{
			this->_location_keyword_check = 0;
			this->_redirection_flag = 0;
			this->_return_flag = 0;
			this->_redirection = "";
			this->_return = "";
		}
		temp = temp.substr(temp.find("}") + strlen("}"), std::string::npos);
		if (StringCheck(temp, '}'))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
	}
	if (_location_braket_open == _location_braket_close && !_location_parse_done && temp.find("}") != std::string::npos)
	{
		if (!this->_location_keyword_check)
		{
			std::cout << "here" << std::endl;//
			this->_err_msg = ErrMsg(this->_config_file_name, LOCATION_BRAKET_CLOSE, *line, i);
			throw (this->_err_msg);
		}
		_server_braket_close++;
		_location_parse_done++;
		std::cout << "server block closed" << std::endl;//
		temp = temp.substr(temp.find("}") + strlen("}"), std::string::npos);
		if (StringCheck(temp, '}'))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
	}
	if (_server_braket_close && temp.find("}") != std::string::npos)
	{
		ServerBlockParse::SetHttpBraketClose(1);
		std::cout << "http block closed" << std::endl;//
		temp = temp.substr(temp.find("}") + strlen("}"), std::string::npos);
		if (StringCheck(temp))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, HTTP_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
	}
	if (_location_braket_close && _server_braket_close)
	{
		std::cout << "server block init" << std::endl;
		ServerBlockParse::InitServerBlockParseData();
		InitLocationBlockParseData();
		ServerBlockParse::SetLocationBlockEnded(1);
	}
}

void	LocationBlockParse::InitLocationBlockParseData(void)
{
	this->_location_keyword_check = 0;
	this->_location_braket_open = 0;
	this->_location_braket_close = 0;
	//this->_server_braket_close = 0;
	this->_location_block_count = 0;
	this->_redirection_flag = 0;
	this->_return_flag = 0;
	this->_cgi_bin_flag = 0;
	this->_root_flag = 0;
	this->_cgi_path_flag = 0;
	this->_cgi_extention_flag = 0;
	this->_redirection = "";
	this->_return = "";
	this->_root = "";
	this->_cgi_path_python = 0;
	this->_cgi_path_bash = 0;
	this->_cgi_path_php = 0;
	this->_cgi_extention_py = 0;
	this->_cgi_extention_sh = 0;
	this->_cgi_extention_php = 0;
	this->_location_parse_done = 0;
	this->_err_msg = "";
}