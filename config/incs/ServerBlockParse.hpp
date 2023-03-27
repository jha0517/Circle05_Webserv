/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerBlockParse.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 00:07:16 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:11:36 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_BLOCK_PARSE_HPP
# define SERVER_BLOCK_PARSE_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include "./HttpBlockParse.hpp"
#include "./ParseUtils.h"
#include "./DefineErrMsg.h"

class	ServerBlockParse: public HttpBlockParse
{
public:
	ServerBlockParse();
	ServerBlockParse(const ServerBlockParse& serverblockparse);
	ServerBlockParse& operator=(const ServerBlockParse& serverblockparse);
	virtual ~ServerBlockParse();

	int		GetListen(void) const;
	std::string	GetHost(void) const;
	int		GetClientMaxBodySize(void) const;
	std::string	GetIndex(void) const;
	int		GetAllowMethodsGet(void) const;
	int		GetAllowMethodsPost(void) const;
	int		GetAllowMethodsDelete(void) const;

	void		SetConfigFileName(std::string config_file_name);

	void		ServerBlockCheck(std::string *line, int i);
	void		ServerBlockKeywordCheck(std::string *line, int i);

protected:
	int		_server_keyword_check;
	int		_server_braket_open;
	int		_server_block;

	int		_listen_flag;
	int		_listen;
	int		_host_flag;
	std::string	_host;
	int		_client_max_body_size_flag;
	int		_client_max_body_size;
	int		_index_flag;
	std::string	_index;
	int		_allow_methods_flag;
	int		_allow_methods_get;
	int		_allow_methods_post;
	int		_allow_methods_delete;

	int		_server_parse_done;
	std::string	_config_file_name;
	std::string	_err_msg;

private:
	void		ServerBlockGetInfo(std::string *token, std::string *line, int i);
};

#endif
