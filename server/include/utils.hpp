/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:13:50 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/05 22:12:55 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
// # include <string>
// # include <map>
// # include <vector>
// # include <fstream>
// # include <set>
// # include <csignal>
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <sys/socket.h>
// # include <sys/types.h>
// # include <netinet/in.h>
// # include <arpa/inet.h>
// # include <ctime>
// # include <iostream>
// # include <ostream>
// # include <sys/stat.h>
// # include <sys/select.h>
// # include <string.h>

// # include "Server.hpp"
// # include "Request.hpp"

// # include <cstddef>
// # include "Client.hpp"


// # include "Uri.hpp"
// # include "MessageHeaders.hpp"
// # include "Cgi.hpp"
// # include "Log.hpp"

// # include "Connection.hpp"

std::string intToString(int a);
std::size_t	vecFind(std::vector<char> rawRequest, std::string str);
std::string	vecSubstr(std::vector<char> rawRequest, size_t start, size_t end);
std::string	check_filename_get_str(const char *filename);
void	printData(std::vector<char> data);
int isDirectory(const char *path);

#endif
