/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:11:11 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/29 14:12:09 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>

std::string intToString(int a)
{
	std::stringstream	ss;

    ss << a;
    return ss.str();
}