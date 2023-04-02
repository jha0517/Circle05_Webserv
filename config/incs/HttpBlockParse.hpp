/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBlockParse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:52:51 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/24 21:36:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BLOCK_PARSE_HPP
# define HTTP_BLOCK_PARSE_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "./ParseUtils.h"
#include "./DefineErrMsg.h"

class	HttpBlockParse
{
public:
	HttpBlockParse();
	HttpBlockParse(const HttpBlockParse& httpblockparse);
	HttpBlockParse& operator=(const HttpBlockParse& httpblockparse);
	virtual ~HttpBlockParse();
	
	std::string	GetRoot(void) const;
	std::string	GetAutoIndex(void) const;
	std::string	GetDefaultErrorPage(void) const;
	std::string	GetErrPageDirectory(void) const;
	int		GetHttpParseDone(void) const;

	void		SetConfigFileName(std::string config_file_name);

	void		HttpBlockCheck(std::string *line, int i);

private:
	void		HttpKeywordCheck(std::string *line, std::string temp, int i, std::string keyword);
	void		HttpKeywordHttpCheck(std::string *line, std::string temp, int i);
	void		HttpBraketOpenCheck(std::string *line, std::string temp, int i);
	void		HttpKeywordTokenCheck(std::string *line, std::string temp, int i);
	void		HttpBlockGetInfo(std::string *token, std::string *line, int i);

	int		_http_keyword_check;
	int		_http_braket_open;
	int		_http_block_count;
	int		_root_flag;
	int		_autoindex_flag;
	int		_default_err_page_flag;
	std::string	_root;
	std::string	_autoindex;
	std::string	_default_err_page;
	std::string	_err_page_directory;
	int		_http_parse_done;
	std::string	_config_file_name;
	std::string	_err_msg;
};

#endif
