/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlockParse.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 00:07:25 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:21:22 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ServerBlockParse.hpp"

ServerBlockParse::ServerBlockParse()
			: _server_keyword_check(0), _server_braket_open(0), _server_block(0),
			_listen_flag(0), _listen(0), _host_flag(0), _host(""),
			_client_max_body_size_flag(0), _client_max_body_size(0),
			_index_flag(0), _index(""), _allow_methods_flag(0),
			_allow_methods_get(0), _allow_methods_post(0), _allow_methods_delete(0),
			_server_parse_done(0), _config_file_name(""), _err_msg("")
{
}

//ServerBlockParse::ServerBlockParse(const ServerBlockParse& serverblockparse)
ServerBlockParse::ServerBlockParse(const ServerBlockParse& serverblockparse): HttpBlockParse(serverblockparse)
{
	*this = serverblockparse;
}

ServerBlockParse& ServerBlockParse::operator=(const ServerBlockParse& serverblockparse)
{
	if (this == &serverblockparse)
		return (*this);
	this->_server_keyword_check = serverblockparse._server_keyword_check;
	this->_server_braket_open = serverblockparse._server_braket_open;
	this->_server_block = serverblockparse._server_block;
	this->_listen_flag = serverblockparse._listen_flag;
	this->_listen = serverblockparse._listen;
	this->_host_flag = serverblockparse._host_flag;
	this->_host = serverblockparse._host;
	this->_client_max_body_size_flag = serverblockparse._client_max_body_size_flag;
	this->_client_max_body_size = serverblockparse._client_max_body_size;
	this->_index_flag = serverblockparse._index_flag;
	this->_index = serverblockparse._index;
	this->_allow_methods_flag = serverblockparse._allow_methods_flag;
	this->_allow_methods_get = serverblockparse._allow_methods_get;
	this->_allow_methods_post = serverblockparse._allow_methods_post;
	this->_allow_methods_delete = serverblockparse._allow_methods_delete;
	this->_server_parse_done = serverblockparse._server_parse_done;
	this->_config_file_name = serverblockparse._config_file_name;
	this->_err_msg = serverblockparse._err_msg;
	return (*this);
}

ServerBlockParse::~ServerBlockParse()
{
}

int	ServerBlockParse::GetListen(void) const
{
	return (this->_listen);
}

std::string	ServerBlockParse::GetHost(void) const
{
	return (this->_host);
}

int	ServerBlockParse::GetClientMaxBodySize(void) const
{
	return (this->_client_max_body_size);
}

std::string	ServerBlockParse::GetIndex(void) const
{
	return (this->_index);
}

int	ServerBlockParse::GetAllowMethodsGet(void) const
{
	return (this->_allow_methods_get);
}

int	ServerBlockParse::GetAllowMethodsPost(void) const
{
	return (this->_allow_methods_post);
}

int	ServerBlockParse::GetAllowMethodsDelete(void) const
{
	return (this->_allow_methods_delete);
}

void	ServerBlockParse::SetConfigFileName(std::string config_file_name)
{
	this->_config_file_name = config_file_name;
}

void	ServerBlockParse::ServerBlockCheck(std::string *line, int i)
{
	std::cout << "SERVER_BLOCK: ";
	std::string	temp = *line;

	if (temp.find("location") != std::string::npos)
		this->_server_parse_done++;
	if (this->_server_parse_done)
		return ;
	if (temp.find("}") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_CLOSE, *line, i);
		throw (this->_err_msg);
	}
	if (this->_server_braket_open && temp.find("{") != std::string::npos)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
		throw (this->_err_msg);
	}

	if (temp.find("server") != std::string::npos)
	{
		if (temp.find("server") != 0 && !StringCheck(temp.substr(0, temp.find("server"))))
			temp = temp.substr(temp.find("server"), std::string::npos);
		if (std::strncmp("server", temp.c_str(), 6))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_SERVER, *line, i);
			throw (this->_err_msg);
		}

		this->_server_keyword_check++;
		if (this->_server_keyword_check == 0 && StringCheck(temp.substr(temp.find("server") + 6, std::string::npos), '{'))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);
		}
		if (temp.find("{") != std::string::npos)
		{
			this->_server_braket_open++;
			if (temp.find("{") != 0 && !StringCheck(temp.substr(0, temp.find("{"))))
				temp = temp.substr(temp.find("{"), std::string::npos);
			if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
				throw (this->_err_msg);
			}
			if (this->_server_keyword_check == 1 && this->_server_braket_open == 1)
			{
				this->_server_block++;
				this->_server_keyword_check--;
				this->_server_braket_open++;
			}
			else
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
				throw (this->_err_msg);
			}
		}
	}
	else if (temp.find("{") != std::string::npos)
	{
		this->_server_braket_open++;
		if (temp.find("{") != 0)
			temp = temp.substr(temp.find("{"), std::string::npos);
		if (temp.substr(temp.find("{") + 1, std::string::npos).find("{") != std::string::npos)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN, *line, i);
			throw (this->_err_msg);

		}
		if (StringCheck(temp.substr(temp.find("{") + 1, std::string::npos))
			&& !(temp.find("listen") != std::string::npos
				|| temp.find("host") != std::string::npos
				|| temp.find("client_max_body_size") != std::string::npos
				|| temp.find("index") != std::string::npos
				|| temp.find("allow_methods") != std::string::npos))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_INVALID_KWD, *line, i);
			throw (this->_err_msg);
		}
		if (this->_server_keyword_check == 1 && this->_server_braket_open == 1)
		{
			this->_server_block++;
			this->_server_keyword_check--;
			this->_server_braket_open++;
		}
	}
	else if (temp.find("listen") != std::string::npos
		|| temp.find("host") != std::string::npos
		|| temp.find("client_max_body_size") != std::string::npos
		|| temp.find("index") != std::string::npos
		|| temp.find("allow_methods") != std::string::npos)
	{
		return ;
	}
	else
	{
		for (int i = 0; i < (int)temp.length(); i++)
		{
			if (!(temp[i] == ' ' || temp[i] == '\t'))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_INVALID_KWD, *line, i);
				throw (this->_err_msg);
			}
		}
		return ;
	}
}

void	ServerBlockParse::ServerBlockKeywordCheck(std::string *line, int i)
{
	std::string	temp = *line;
	std::string	token[100] = {"", };

	if (temp.find("server") != std::string::npos)
		temp = temp.substr(temp.find("server") + 6, std::string::npos);
	if (temp.find("listen") != std::string::npos)
	{
		if (temp.find("listen") != 0 && !StringCheck(temp.substr(0, temp.find("listen")), '{'))
			temp = temp.substr(temp.find("listen"), std::string::npos);
		if (TokenCount(2, temp, token) && !_server_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_LISTEN, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("host") != std::string::npos)
	{
		if (temp.find("host") != 0 && !StringCheck(temp.substr(0, temp.find("host")), '{'))
			temp = temp.substr(temp.find("host"), std::string::npos);
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_HOST, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("client_max_body_size") != std::string::npos)
	{
		if (temp.find("client_max_body_size") != 0 && !StringCheck(temp.substr(0, temp.find("client_max_body_size")), '{'))
			temp = temp.substr(temp.find("client_max_body_size"), std::string::npos);
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_CLIENT_MAX_BODY_SIZE, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("index") != std::string::npos)
	{
		if (temp.find("index") != 0 && !StringCheck(temp.substr(0, temp.find("index")), '{'))
			temp = temp.substr(temp.find("index"), std::string::npos);
		if (TokenCount(2, temp, token) && !this->_server_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_INDEX, *line, i);
			throw (this->_err_msg);
		}
	}
	else if (temp.find("allow_methods") != std::string::npos)
	{
		if (temp.find("allow_methods") != 0 && !StringCheck(temp.substr(0, temp.find("allow_methods")), '{'))
			temp = temp.substr(temp.find("allow_methods"), std::string::npos);
		if (!(TokenCount(temp, token) == 2 || TokenCount(temp, token) == 3 || TokenCount(temp, token) == 4)
			&& !this->_server_parse_done)
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
			throw (this->_err_msg);
		}
		this->_allow_methods_flag = TokenCount(temp, token) - 1;
	}
	ServerBlockGetInfo(token, line, i);
	if (this->_listen != 0 && this->_host != "" && this->_client_max_body_size != 0 && this->_index != "" && this->_allow_methods_flag == 1)
		this->_server_parse_done = 1;
	if (this->_server_parse_done && !this->_server_braket_open)
	{
		this->_err_msg = ErrMsg(this->_config_file_name, SERVER_BRAKET_OPEN);
		throw (this->_err_msg);
	}
}

void	ServerBlockParse::ServerBlockGetInfo(std::string *token, std::string *line, int i)
{
	if (token[0] == "listen" && !_server_parse_done)
	{
		//number check, number range check
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_listen_flag++;
		this->_listen = atoi(token[1].substr(0, token[1].length() - 1).c_str());
	}
	if (token[0] == "host" && !_server_parse_done)
	{
		//ip address check
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_host_flag++;
		this->_host = token[1].substr(0, token[1].length() - 1);
	}
	if (token[0] == "client_max_body_size" && !_server_parse_done)
	{
		//number check, number range check
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_client_max_body_size_flag++;
		this->_client_max_body_size = atoi(token[1].substr(0, token[1].length() - 1).c_str());
	}
	if (token[0] == "index" && !_server_parse_done)
	{
		//if (CheckValidPath(token[1]))
		//	return (1);
		//check if the path is valid
		if (SemicolonCheck(token[1]))
		{
			this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
			throw (this->_err_msg);
		}
		this->_index_flag++;
		this->_index = HttpBlockParse::GetRoot().append("/") + token[1].substr(0, token[1].length() - 1);
	}
	if (token[0] == "allow_methods" && !_server_parse_done)
	{
		if (this->_allow_methods_flag == 1)
		{
			if (SemicolonCheck(token[1]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!(token[1] == "GET;"))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
			this->_allow_methods_get = 1;
		}
		else if (this->_allow_methods_flag == 2)
		{
			if (SemicolonCheck(token[2]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!(token[1] == "GET" && token[2] == "POST;"))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
			this->_allow_methods_get = 1;
			this->_allow_methods_post = 1;
		}
		else
		{
			if (SemicolonCheck(token[3]))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_SEMICOLON, *line, i);
				throw (this->_err_msg);
			}
			if (!(token[1] == "GET" && token[2] == "POST" && token[3] == "DELETE;"))
			{
				this->_err_msg = ErrMsg(this->_config_file_name, SERVER_KWD_ALLOW_METHODS, *line, i);
				throw (this->_err_msg);
			}
			this->_allow_methods_get = 1;
			this->_allow_methods_post = 1;
			this->_allow_methods_delete = 1;
		}
		this->_allow_methods_flag = 1;
	}
}
