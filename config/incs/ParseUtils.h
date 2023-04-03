/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseUtils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostin <acostin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 04:20:03 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/03 02:03:59 by acostin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include "./DefineErrMsg.h"

# define BLACK			"\x1b[0m"
# define RED			"\x1b[31m"
# define CYAN			"\x1b[36m"
# define YELLOW			"\x1b[33m"

int		StringCheck(std::string str);
int		StringCheck(std::string str, char c);
int		SemicolonCheck(std::string str);
std::string	RemoveSpaceTab(std::string str);
int		TokenCount(int n, std::string line, std::string *token);
int		TokenCount(std::string line, std::string *token);
std::string	ErrMsg(std::string file_name, int err_number, std::string line, int i);

#endif
