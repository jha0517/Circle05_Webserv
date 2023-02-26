/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:13:17 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/26 17:48:12 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_H
# define WEBSERV_H
# include <sys/socket.h>
# include <netinet/in.h>
# include <stdio.h>
# include <iostream>
# include <stdlib.h>
# include <vector>
# include <string.h>
# include <unistd.h>

# include "../src/server/ServerManager.hpp"
# include "../src/server/Config.hpp"
# include "../src/server/Request.hpp"
# include "../src/server/Response.hpp"

#endif