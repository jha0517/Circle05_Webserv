/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LocationBlockParse.hpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostin <acostin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 01:19:40 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/03 01:05:55 by acostin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_BLOCK_PARSE_HPP
# define LOCATION_BLOCK_PARSE_HPP

#include <iostream>
#include <string>
#include "./ServerBlockParse.hpp"
#include "./ParseUtils.h"
#include "./DefineErrMsg.h"

class	LocationBlockParse: public ServerBlockParse
{
public:
	LocationBlockParse();
	LocationBlockParse(const LocationBlockParse& locationblockparse);
	LocationBlockParse& operator=(const LocationBlockParse& locationblockparse);
	~LocationBlockParse();

	std::string	GetRedirectionLocationPath(void) const;
	std::string	GetReturn(void) const;
	std::string	GetIndexLocationPath(void) const;
	std::string	GetIndex(void) const;
	std::string	GetCgiLocationPath(void) const;
	int		GetCgiPathPhp(void) const;
	int		GetCgiExtentionPhp(void) const;
	int		GetLocationParseDone(void) const;
	int		GetLocationBlockCount(void) const;
	int		GetServerBraketClose(void) const;

	void		SetConfigFileName(std::string config_file_name);

	void		LocationBlockCheck(std::string *line, int i);

private:
	void		ServerMissedKeywordCheck(std::string *line, std::string temp, int i);
	void		LocationMissedKeywordCheck(std::string *line, int i);

	void		LocationKeywordCheck(std::string *line, std::string temp, int i, std::string keyword);
	void		LocationKeywordLocationCheck(std::string *line, std::string temp, int i);
	void		LocationBraketOpenCheck(std::string *line, std::string temp, int i);
	void		LocationKeywordTokenCheck(std::string *line, std::string temp, int i);
	void		LocationBlockGetInfo(std::string *token, std::string *line, std::string temp, int i);
	void		LocationBraketCloseCheck(std::string *line, std::string temp, int i);

	void		InitLocationBlockParseData(void);

	int		_location_keyword_check;
	int		_location_braket_open;
	int		_location_braket_close;
	int		_server_braket_close;
	int		_location_block_count;

	int		_redirection_location_flag;
	int		_return_flag;
	int		_index_location_flag;
	int		_index_flag;
	int		_cgi_location_flag;
	int		_cgi_path_flag;
	int		_cgi_extention_flag;

	std::string	_redirection_location_path;
	std::string	_return;
	std::string	_index_location_path;
	std::string	_index;
	std::string	_cgi_location_path;
	int		_cgi_path_php;
	int		_cgi_extention_php;

	int		_location_parse_done;
	std::string	_config_file_name;
	std::string	_err_msg;
};

#endif
