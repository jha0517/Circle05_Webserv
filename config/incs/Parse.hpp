/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parse.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostin <acostin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:54:20 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/03 02:12:06 by acostin          ###   ########.fr       */
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

private:
	int		FileOpen(std::string config_file_name);
	int		_total_server_block;
};

#endif
