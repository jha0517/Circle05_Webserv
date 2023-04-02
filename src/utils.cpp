/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:11:11 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/02 14:10:21 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <vector>
# include <fstream>
# include <iostream>

std::string intToString(int a)
{
	std::stringstream	ss;

    ss << a;
    return ss.str();
}

std::size_t	vecFind(std::vector<char> rawRequest, std::string str)
{
	size_t	i = 0;
	size_t	v = 0;

	for (std::vector<char>::iterator it = rawRequest.begin(); it != rawRequest.end(); ++it)
	{
		i = 0;
		if (*it == str[i])
		{
			while (*(it + i) == str[i])
			{
				// printf("Comparing vector char %c with str %c\n", *(it + 1), str[i]);
				// printf("i is %li, str.length is %li, returning %li\n", i, str.length()-1, v);
				if (i == str.length() - 1)
					return (v);
				i++;
			}
		}
		v++;
	}
	return (std::string::npos);
}

std::string	vecSubstr(std::vector<char> rawRequest, size_t start, size_t end)
{
	size_t	i = 0;
	size_t	v = 0;
	std::string	ret;

	for (std::vector<char>::iterator it = rawRequest.begin(); it != rawRequest.end(); ++it)
	{
		if (v == start)
		{
			i = 0;
			while (i != end - start)
			{
				ret += *(it + i);
				i++;
			}
		}
		v++;
	}
	return (ret);
}

std::string	check_filename_get_str(const char *filename)
{
	std::string		src;
	std::string		null;
	std::string		buffer;
	std::ifstream	ifs;
	char	c;
	
	ifs.open(filename);
	if (!ifs)
	{
		std::cout << filename <<"File non-existance or Right Denied!" << std::endl;
		return (null);
	}
	while (ifs.get(c))
		src+= c;
	ifs.close();
	if (src.empty())
	{
		std::cout << "File is empty!" << std::endl;
		return (null);
	}
	return (src);
}