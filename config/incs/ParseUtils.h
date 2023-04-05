/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseUtils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 04:20:03 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/05 13:20:37 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include "./DefineErrMsg.h"

# define _BLACK			"\x1b[0m"
# define _RED			"\x1b[31m"
# define _CYAN			"\x1b[36m"
# define _YELLOW			"\x1b[33m"
# define _MAGENTA		"\x1b[35m"

int			StringCheck(std::string str);
int			StringCheck(std::string str, char c);
int			SemicolonCheck(std::string str);
std::string		RemoveSpaceTab(std::string str);
int			TokenCount(int n, std::string line, std::string *token);
int			TokenCount(std::string line, std::string *token);
std::string		ErrMsg(std::string file_name, int err_number, std::string line, int i);

#endif
