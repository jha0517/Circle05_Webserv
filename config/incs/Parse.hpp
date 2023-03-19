/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/19 19:47:04 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

typedef struct s_http
{
	int	root;
	int	autoindex;
	int	default_error_page;
}	t_http;

typedef struct s_server
{
	int	listen;
	int	host;
	int	client_max_body_size;
	int	index;
	int	allow_methods;
	int	location_redir;
	int	location_cgi;
}	t_server;

class	Parse
{
public:
	Parse(std::string config_file);
	~Parse();

	class	FileOpenFailedException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidHttpBlockException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	class	InvalidServerBlockException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

private:
	Parse();
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);

	std::string	ReplaceLine(std::string line, std::string s1, std::string s2);
	int		TokenCount(int n, std::string line);
	int		CheckValidPath(std::string path);
	int		CheckValidErrorPage(std::string path);
	int		GetInfo(std::string key, std::string value);

	int		FileOpen(std::string config_file);
	void		HttpBlockCheck(std::string *line);
	void		HttpBlockElementCheck(std::string *line);

	void		ServerBlockCheck(std::string *line);

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

	int		_server_keyword_check;
	int		_server_block;
	int		_location_block;
};

#endif
