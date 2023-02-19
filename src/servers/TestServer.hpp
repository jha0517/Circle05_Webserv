/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:27:35 by hyunah            #+#    #+#             */
/*   Updated: 2023/02/19 17:03:28 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSERVER_H
# define TESTSERVER_H
# include "SimpleServer.hpp"
# include <unistd.h>
# include <string>
# include <cstring>

class TestServer : public SimpleServer
{
private:
	char	buffer[30000];
	int		new_socket;
	void accepter(void);
	void handler(void);
	void responder(void);

public:
	TestServer(void);
	~TestServer(void);
	void launch(void);
};

#endif