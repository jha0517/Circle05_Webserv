/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:14:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_HPP
# define PARSE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include "./HttpBlockParse.hpp"
#include "./ServerBlockParse.hpp"
#include "./DefineErrMsg.h"

//class	Parse: public HttpBlockParse, public ServerBlockParse
class	Parse: public ServerBlockParse
{
public:
	Parse();
	Parse(std::string config_file_name);
	Parse(const Parse& parse);
	Parse& operator=(const Parse& parse);
	~Parse();

	class	FileOpenFailedException: public std::exception
	{
	public:
		virtual const char*	what(void) const throw();
	};


private:
	int		FileOpen(std::string config_file_name);

	std::string	_root;
	std::string	_autoindex;
	std::string	_default_err_page;
	std::string	_err_page_directory;

	

	int		_server_block;
	int		_location_block;

	std::string	_config_file_name;
	std::string	_err_msg;
};

#endif
