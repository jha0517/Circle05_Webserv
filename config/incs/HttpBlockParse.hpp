/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBlockParse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:52:51 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:17:27 by yhwang           ###   ########.fr       */
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

	void		SetConfigFileName(std::string config_file_name);

	void		HttpBlockCheck(std::string *line, int i);
	void		HttpBlockKeywordCheck(std::string *line, int i);

protected:
	int		_http_keyword_check;
	int		_http_braket_open;
	int		_http_block;

	int		_root_flag;
	std::string	_root;
	int		_autoindex_flag;
	std::string	_autoindex;
	int		_default_err_page_flag;
	std::string	_default_err_page;
	std::string	_err_page_directory;

	int		_http_parse_done;
	std::string	_config_file_name;
	std::string	_err_msg;

private:
	void		HttpBlockGetInfo(std::string *token, std::string *line, int i);
};

#endif
