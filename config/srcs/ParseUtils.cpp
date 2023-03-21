/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseUtils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 04:20:47 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/20 04:21:28 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ParseUtils.h"

int	StringCheck(std::string str)
{
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
			return (1);
	}
	return (0);
}

int	StringCheck(std::string str, char c)
{
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == c))
			return (1);
	}
	return (0);
}
