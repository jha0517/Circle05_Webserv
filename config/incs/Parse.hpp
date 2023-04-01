/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/01 07:45:26 by yhwang           ###   ########.fr       */
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
#include "./LocationBlockParse.hpp"
#include "./ParseUtils.h"
#include "./DefineErrMsg.h"

class	Parse: public LocationBlockParse
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

	int		_listen;
	std::string	_host;
	int		_client_max_body_size;
	std::string	_index;
	int		_allow_methods_get;
	int		_allow_methods_post;
	int		_allow_methods_delete;

	

	int		_server_block_count;
	int		_location_block_count;

	std::string	_config_file_name;
	std::string	_err_msg;
};

#endif
