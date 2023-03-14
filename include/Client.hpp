/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/13 17:20:44 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <string>
# include <stdlib.h>
# include "Uri.hpp"
# include "MessageHeaders.hpp"

struct	Response{
	unsigned int	statusCode;
	std::string		reasonPhrase;
	Uri				target;
	MessageHeaders	headers;
};

class Client
{
private:
	Response	response;

public:
	Client();
	~Client();
	Response	*parseResponse(const std::string &rawReponse);
};

#endif