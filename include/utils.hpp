/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:13:50 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/04 18:06:47 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

std::string intToString(int a);
std::size_t	vecFind(std::vector<char> rawRequest, std::string str);
std::string	vecSubstr(std::vector<char> rawRequest, size_t start, size_t end);
std::string	check_filename_get_str(const char *filename);
