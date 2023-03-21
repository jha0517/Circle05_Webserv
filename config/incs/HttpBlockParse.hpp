/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpBlockParse.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:52:51 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/20 04:21:16 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_BLOCK_PARSE_HPP
# define HTTP_BLOCK_PARSE_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstring>
#include "./ParseUtils.h"

class	HttpBlockParse
{
public:
	HttpBlockParse();
	HttpBlockParse(const HttpBlockParse& httpblockparse);
	HttpBlockParse& operator=(const HttpBlockParse& httpblockparse);
	virtual ~HttpBlockParse();

	class	InvalidBraketOpenException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidKwdHttpException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidKwdRootException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidKwdAutoIdxException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidKwdErrPageException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	MissedRootException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	MissedAutoIdxException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	MissedErrPageException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidCharacterException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};
	
	std::string	GetRoot(void) const;
	std::string	GetAutoIndex(void) const;
	std::string	GetDefaultErrorPage(void) const;
	std::string	GetErrPageDirectory(void) const;

	void		HttpBlockCheck(std::string *line);
	void		HttpBlockElementCheck(std::string *line);




	int		CheckValidPath(std::string path);
	int		CheckValidErrorPage(std::string path);
	int		GetInfo(std::string key, std::string value);
	int		TokenCount(int n, std::string line);

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
};

#endif
