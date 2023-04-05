/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:44 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/15 11:42:39 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H
# include <string>
# include <stdlib.h>
# include "Response.hpp"

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
