/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/20 01:40:58 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "./HttpBlockParse.hpp"

class	Parse: public HttpBlockParse
{
public:
	Parse();
	Parse(std::string config_file);
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	class	FileOpenFailedException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};

	// class	InvalidServerBlockException: public std::exception
	// {
	// public:
	// 	virtual const char*	what(void) const throw();
	// };

private:
	int		FileOpen(std::string config_file);
	//void		ServerBlockCheck(std::string *line);

	std::string	_root;
	std::string	_autoindex;
	std::string	_default_err_page;
	std::string	_err_page_directory;


	int		_server_keyword_check;
	int		_server_block;
	int		_location_block;
};

#endif
